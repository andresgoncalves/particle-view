#ifndef STORY_LOADER_VECTOR_PROPERTY_ROW
#define STORY_LOADER_VECTOR_PROPERTY_ROW

#include <array>

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include "StoryLoaderPropertyRow.h"
#include "../../loaders/StoryLoader.h"

class StoryLoaderVectorPropertyRow : public StoryLoaderPropertyRow
{
public:
  StoryLoaderVectorPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderVectorPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count) override;

  std::array<int, 3> getValues() const;

private:
  std::array<QComboBox *, 3> comboBoxes;
};

#endif