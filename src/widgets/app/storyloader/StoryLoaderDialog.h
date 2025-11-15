#ifndef STORY_LOADER_DIALOG_H
#define STORY_LOADER_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

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
  /** Get dimensionality */
  ViewController::Dimensionality getDimensionality() const;

private:
  StoryLoaderPropertyGrid *particlePropertyGrid;
  StoryLoaderPropertyGrid *scenePropertyGrid;

  QRadioButton *dimensionality2DButton;
  QRadioButton *dimensionality3DButton;

  AppContext &appContext;
};

#endif