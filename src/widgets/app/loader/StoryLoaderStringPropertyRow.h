#ifndef STORY_LOADER_STRING_PROPERTY_ROW
#define STORY_LOADER_STRING_PROPERTY_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <loaders/StoryLoader.h>

#include "StoryLoaderPropertyRow.h"

class StoryLoaderStringPropertyRow : public StoryLoaderPropertyRow
{
public:
  StoryLoaderStringPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderStringPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count) override;

  StoryLoader::IndexType getValue() const;

private:
  QComboBox *comboBox;
};

#endif