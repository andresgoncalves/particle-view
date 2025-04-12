#ifndef STORY_LOADER_PROPERTY_GRID
#define STORY_LOADER_PROPERTY_GRID

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include "StoryLoaderPropertyRow.h"
#include "../../loaders/StoryLoader.h"

class StoryLoaderPropertyGrid : public QWidget
{
public:
  StoryLoaderPropertyGrid(QWidget *parent = nullptr);

  void setCount(int count);

  std::map<StoryLoader::DefaultProperty, int> getDefaultProperties() const;
  std::map<std::string, int> getCustomProperties() const;

private:
  void addCustomProperty(std::string property);
  void removeCustomProperty(std::string property);

  int count;

  QVBoxLayout *itemLayout;

  std::map<StoryLoader::DefaultProperty, StoryLoaderPropertyRow *> defaultRows;
  std::map<std::string, StoryLoaderPropertyRow *> customRows;
};

#endif