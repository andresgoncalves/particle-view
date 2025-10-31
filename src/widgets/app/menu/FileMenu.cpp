#include "FileMenu.h"

#include <fstream>

#include <QtWidgets/QFileDialog>
#include <QtOpenGL/QOpenGLFramebufferObject>
#include <QtOpenGL/QOpenGLPaintDevice>

#include <widgets/app/export/ExportDialog.h>
#include <widgets/app/storyloader/StoryLoaderDialog.h>
#include <graphics/renderers/SceneRenderer.h>

FileMenu::FileMenu(AppContext &appContext, QWidget *parent) : QMenu{"Archivo", parent}, appContext{appContext}
{
  auto dialogParent = parent ? parent : this;

  auto openFileAction = addAction("Abrir archivo", QKeySequence::StandardKey::Open);
  connect(openFileAction, &QAction::triggered, this,
          [=, this, &appContext]()
          {
            auto fileName = QFileDialog::getOpenFileName(dialogParent, "Seleccionar archivo").toStdString();
            if (!fileName.empty())
            {
              auto fileStream = std::ifstream{fileName};
              auto storyLoader = StoryLoader{};
              storyLoader.load(fileStream);

              auto storyLoaderDialog = new StoryLoaderDialog{storyLoader.getScenePropertyCount(), storyLoader.getParticlePropertyCount(), appContext, dialogParent};
              if (storyLoaderDialog->exec() == QDialog::Accepted)
              {
                auto particleProperties = storyLoaderDialog->getParticleProperties();
                auto sceneProperties = storyLoaderDialog->getSceneProperties();
                storyLoader.setParticleProperties(particleProperties);
                storyLoader.setSceneProperties(sceneProperties);

                auto story = storyLoader.parse();

                appContext.animationController.setStory(story);
                appContext.animationController.setAnimationSpeed(6.0 * (story.metadata.endTime - story.metadata.startTime) / story.scenes.size());
                appContext.viewController.setOrigin(story.getOrigin());
                appContext.viewController.setBaseScale(story.getBaseScale());
              }
              storyLoaderDialog->deleteLater();
            }
          });

  auto exportAction = addAction("Exportar animación");
  connect(exportAction, &QAction::triggered, this,
          [=, this, &appContext]()
          {
            auto exportDialog = new ExportDialog{appContext, dialogParent};
            if (exportDialog->exec() == QDialog::Accepted)
            {
              auto directoryName = QFileDialog::getExistingDirectory(parent ? parent : this, "Seleccionar directorio", "").toStdString();
              if (!directoryName.empty())
              {
                // Render to image
                auto oldViewport = appContext.viewController.getViewport();
                appContext.viewController.setViewport({1.0f, 720.0f / 1280.0f});
                appContext.viewController.updateViewProjectionMatrix();
                glPushAttrib(GL_VIEWPORT_BIT);
                glViewport(0, 0, 1280, 720);

                QOpenGLFramebufferObjectFormat frameBufferFormat;
                frameBufferFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
                frameBufferFormat.setTextureTarget(GL_TEXTURE_2D);
                frameBufferFormat.setInternalTextureFormat(GL_RGBA);

                auto frameBuffer = QOpenGLFramebufferObject{{1280, 720}, frameBufferFormat};
                frameBuffer.bind();

                float timeStep = 1.0f / 2.0f;
                float animationSpeed = 100.0f;

                auto minTime = appContext.animationController.getFirstScene().getTime();
                auto maxTime = appContext.animationController.getLastScene().getTime();

                auto paintDevice = QOpenGLPaintDevice{};
                auto painter = QPainter{&paintDevice};
                auto renderContext = RenderContext{frameBuffer.size(), painter, appContext};

                float time = 0.0f;
                float computedTime = minTime;
                int frame = 1;
                auto renderer = SceneRenderer{};
                do
                {
                  auto scene = appContext.animationController.getScene(computedTime);

                  renderer.render(scene, renderContext);

                  auto image = frameBuffer.toImage();
                  image.save(QString("%1/%2.png").arg(directoryName.c_str()).arg(frame, 5, 10, QChar('0')));

                  frame += 1;
                  time += timeStep;
                  computedTime = minTime + time * animationSpeed;
                } while (computedTime <= maxTime);

                frameBuffer.release();
                appContext.viewController.setViewport(oldViewport);
                appContext.viewController.updateViewProjectionMatrix();
                glPopAttrib();
              }
            }
            exportDialog->deleteLater();
          });
}