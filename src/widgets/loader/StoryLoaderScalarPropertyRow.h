#ifndef STORY_LOADER_SCALAR_PROPERTY_ROW
#define STORY_LOADER_SCALAR_PROPERTY_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include "../../loaders/StoryLoader.h"

class StoryLoaderScalarPropertyRow : public QWidget
{
public:
  StoryLoaderScalarPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderScalarPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count);

  int getValue() const;
  QPushButton *getDeleteButton() const;

private:
  QComboBox *comboBox;
  QPushButton *deleteButton;
};

#endif