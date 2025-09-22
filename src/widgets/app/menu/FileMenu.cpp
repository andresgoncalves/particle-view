#include "FileMenu.h"

#include <fstream>

#include <QtWidgets/QFileDialog>

#include <widgets/app/storyloader/StoryLoaderDialog.h>

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

              auto storyLoaderDialog = new StoryLoaderDialog{storyLoader.getParticlePropertyCount(), storyLoader.getScenePropertyCount(), appContext, dialogParent};
              if (storyLoaderDialog->exec() == QDialog::Accepted)
              {
                auto particleProperties = storyLoaderDialog->getParticleProperties();
                auto sceneProperties = storyLoaderDialog->getSceneProperties();
                storyLoader.setParticleProperties(particleProperties);
                storyLoader.setSceneProperties(sceneProperties);

                auto story = storyLoader.parse();

                appContext.animationController.setStory(story);
                appContext.animationController.setAnimationSpeed(6.0 * (story.metadata.endTime - story.metadata.startTime) / story.scenes.size());
                appContext.viewController.setOrigin((story.metadata.start + story.metadata.end) / 2);

                auto diagonalSize = story.metadata.start.distanceToPoint(story.metadata.end);
                appContext.viewController.setBaseScale(diagonalSize > 0 ? 1.0f / diagonalSize : 1.0f);
              }
              storyLoaderDialog->deleteLater();
            }
          });
}