#ifndef STORY_LOADER_DIALOG_H
#define STORY_LOADER_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>

#include "StoryLoaderPropertyGrid.h"
#include "../../controllers/AppContext.h"

class StoryLoaderDialog : public QDialog
{
public:
  StoryLoaderDialog(AppContext &appContext, QWidget *parent = nullptr);

private:
  QLineEdit *selectFileTextField;
  StoryLoaderPropertyGrid *propertyGrid;

  AppContext &appContext;
};

#endif