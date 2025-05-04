#ifndef STORY_LOADER_SCALAR_PROPERTY_ROW
#define STORY_LOADER_SCALAR_PROPERTY_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include "StoryLoaderPropertyRow.h"
#include "../../loaders/StoryLoader.h"

class StoryLoaderScalarPropertyRow : public StoryLoaderPropertyRow
{
public:
  StoryLoaderScalarPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderScalarPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count) override;

  int getValue() const;

private:
  QComboBox *comboBox;
};

#endif