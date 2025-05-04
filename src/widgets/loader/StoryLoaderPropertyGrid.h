#ifndef STORY_LOADER_PROPERTY_GRID
#define STORY_LOADER_PROPERTY_GRID

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include "StoryLoaderScalarPropertyRow.h"
#include "StoryLoaderVectorPropertyRow.h"
#include "../../loaders/StoryLoader.h"

class StoryLoaderPropertyGrid : public QWidget
{
public:
  StoryLoaderPropertyGrid(QWidget *parent = nullptr);

  void setCount(int count);

  std::map<StoryLoader::DefaultProperty, int> getDefaultProperties() const;
  std::map<std::string, int> getScalarProperties() const;
  std::map<std::string, std::array<int, 3>> getVectorProperties() const;

  void addCustomProperty(std::string property, Particle::PropertyType type);
  void removeCustomProperty(std::string property);

private:
  int count;

  QVBoxLayout *itemLayout;

  std::map<StoryLoader::DefaultProperty, StoryLoaderScalarPropertyRow *> defaultRows;
  std::map<std::string, StoryLoaderScalarPropertyRow *> scalarRows;
  std::map<std::string, StoryLoaderVectorPropertyRow *> vectorRows;
};

#endif