#ifndef STORY_LOADER_VECTOR_PROPERTY_ROW
#define STORY_LOADER_VECTOR_PROPERTY_ROW

#include <array>

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include <loaders/StoryLoader.h>

#include "StoryLoaderPropertyRow.h"

class StoryLoaderVectorPropertyRow : public StoryLoaderPropertyRow
{
public:
  StoryLoaderVectorPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderVectorPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count) override;

  StoryLoader::IndicesType getValues() const;

private:
  std::array<QComboBox *, 3> comboBoxes;
};

#endif