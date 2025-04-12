#ifndef STORY_LOADER_PROPERTY_ROW
#define STORY_LOADER_PROPERTY_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include "../../loaders/StoryLoader.h"

class StoryLoaderPropertyRow : public QWidget
{
public:
  StoryLoaderPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count);

  QComboBox *getComboBox() const;
  QPushButton *getDeleteButton() const;

private:
  QComboBox *comboBox;
  QPushButton *deleteButton;
};

#endif