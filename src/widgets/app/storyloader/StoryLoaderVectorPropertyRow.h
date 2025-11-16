#ifndef STORY_LOADER_VECTOR_PROPERTY_ROW
#define STORY_LOADER_VECTOR_PROPERTY_ROW

#include <array>

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include <loaders/StoryLoader.h>
#include <widgets/shared/controls/Control.h>

#include "StoryLoaderPropertyRow.h"

class StoryLoaderVectorPropertyRow : public StoryLoaderPropertyRow
{
public:
  StoryLoaderVectorPropertyRow(const char *title, QWidget *parent = nullptr);
  StoryLoaderVectorPropertyRow(const char *title, bool canDelete, QWidget *parent = nullptr);

  void setCount(int count) override;

  /** Set which components should be visible */
  void setVisibleComponents(std::array<bool, 3> components);

  StoryLoader::IndicesType getValues() const;

private:
  std::array<Control<QComboBox> *, 3> controls;
};

#endif