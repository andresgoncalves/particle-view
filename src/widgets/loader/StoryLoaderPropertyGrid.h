#ifndef STORY_LOADER_PROPERTY_GRID
#define STORY_LOADER_PROPERTY_GRID

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include "../../loaders/CustomLoader.h"

class StoryLoaderPropertyGrid : public QWidget
{
public:
  StoryLoaderPropertyGrid(QWidget *parent = nullptr);

  void setCount(int count);
  std::map<CustomLoader::DefaultProperty, int> getDefaultProperties() const;

private:
  std::map<CustomLoader::DefaultProperty, QComboBox *> selectors;
};

#endif