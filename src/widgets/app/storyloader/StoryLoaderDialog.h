#ifndef STORY_LOADER_DIALOG_H
#define STORY_LOADER_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>

#include <controllers/AppContext.h>

#include "StoryLoaderPropertyGrid.h"

class StoryLoaderDialog : public QDialog
{
public:
  StoryLoaderDialog(AppContext &appContext, QWidget *parent = nullptr);

  StoryLoaderDialog(int sceneColumnCount, int particleColumnCount, AppContext &appContext, QWidget *parent = nullptr);

  /** Get particle row properties */
  StoryLoader::PropertyDefinitionMap getParticleProperties() const;
  /** Get scene row properties */
  StoryLoader::PropertyDefinitionMap getSceneProperties() const;

private:
  StoryLoaderPropertyGrid *particlePropertyGrid;
  StoryLoaderPropertyGrid *scenePropertyGrid;

  AppContext &appContext;
};

#endif