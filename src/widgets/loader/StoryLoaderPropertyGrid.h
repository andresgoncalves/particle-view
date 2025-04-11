#ifndef STORY_LOADER_PROPERTY_GRID
#define STORY_LOADER_PROPERTY_GRID

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include "../../loaders/StoryLoader.h"

class StoryLoaderPropertyGrid : public QWidget
{
public:
  StoryLoaderPropertyGrid(QWidget *parent = nullptr);

  void setCount(int count);
  std::map<StoryLoader::DefaultProperty, int> getDefaultProperties() const;

private:
  std::map<StoryLoader::DefaultProperty, QComboBox *> selectors;
};

#endif