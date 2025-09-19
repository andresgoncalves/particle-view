#ifndef STORY_LOADER_PROPERTY_GRID
#define STORY_LOADER_PROPERTY_GRID

#include <map>
#include <string>

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include <loaders/StoryLoader.h>

#include "StoryLoaderPropertyRow.h"

class StoryLoaderPropertyGrid : public QWidget
{
public:
  StoryLoaderPropertyGrid(QWidget *parent = nullptr);

  void setCount(int count);

  std::map<std::string, StoryLoader::PropertyDefinition> getProperties() const;

  void addCustomProperty(std::string property, PropertyType type);
  void removeCustomProperty(std::string property);

private:
  int count;

  QVBoxLayout *itemLayout;

  std::map<std::string, StoryLoaderPropertyRow *> propertyRows;
};

#endif