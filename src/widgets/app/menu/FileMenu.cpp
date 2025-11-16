#include "FileMenu.h"

#include <fstream>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
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
                // Open status dialog
                auto statusMessageBox = QMessageBox{QMessageBox::Icon::NoIcon, "Cargando datos", "Cargando datos...", QMessageBox::NoButton, parent ? parent : this};
                statusMessageBox.setWindowModality(Qt::WindowModality::WindowModal);
                statusMessageBox.show();

                auto particleProperties = storyLoaderDialog->getParticleProperties();
                auto sceneProperties = storyLoaderDialog->getSceneProperties();
                storyLoader.setParticleProperties(particleProperties);
                storyLoader.setSceneProperties(sceneProperties);

                auto story = storyLoader.parse();

                appContext.viewController.setDimensionality(storyLoaderDialog->getDimensionality());
                appContext.animationController.setStory(story);

                // Close status dialog
                statusMessageBox.close();
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
                // Open status dialog
                auto statusMessageBox = QMessageBox{QMessageBox::Icon::NoIcon, "Exportando animación", "Exportando animación...", QMessageBox::NoButton, parent ? parent : this};
                statusMessageBox.setWindowModality(Qt::WindowModality::WindowModal);
                statusMessageBox.show();

                QSize size = exportDialog->getSize();

                // Render to image
                auto oldViewport = appContext.viewController.getViewport();

                if (size.width() > size.height())
                  appContext.viewController.setViewport({1.0f, static_cast<float>(size.height()) / size.width()});
                else
                  appContext.viewController.setViewport({static_cast<float>(size.width()) / size.height(), 1.0f});

                appContext.viewController.updateViewProjectionMatrix();
                glPushAttrib(GL_VIEWPORT_BIT);
                glViewport(0, 0, size.width(), size.height());

                QOpenGLFramebufferObjectFormat frameBufferFormat;
                frameBufferFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
                frameBufferFormat.setTextureTarget(GL_TEXTURE_2D);
                frameBufferFormat.setInternalTextureFormat(GL_RGBA);

                auto frameBuffer = QOpenGLFramebufferObject{size, frameBufferFormat};
                frameBuffer.bind();

                float timeStep = exportDialog->getAnimationSpeed() / exportDialog->getFramesPerSecond();
                auto minTime = appContext.animationController.getFirstScene().getTime();
                auto maxTime = appContext.animationController.getLastScene().getTime();

                auto paintDevice = QOpenGLPaintDevice{size};
                auto painter = QPainter{&paintDevice};
                auto renderContext = RenderContext{frameBuffer.size(), painter, appContext};

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
                  computedTime += timeStep;
                } while (computedTime <= maxTime);

                frameBuffer.release();
                appContext.viewController.setViewport(oldViewport);
                appContext.viewController.updateViewProjectionMatrix();
                glPopAttrib();

                // Close status dialog
                statusMessageBox.close();
              }
            }
            exportDialog->deleteLater();
          });
}