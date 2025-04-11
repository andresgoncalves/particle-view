#include "StoryLoaderPropertyGrid.h"

#include <map>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

StoryLoaderPropertyGrid::StoryLoaderPropertyGrid(QWidget *parent) : QWidget{parent}
{
  auto layout = new QGridLayout{this};

  selectors[StoryLoader::DefaultProperty::X] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::Y] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::Z] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::VX] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::VY] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::VZ] = new QComboBox{this};
  selectors[StoryLoader::DefaultProperty::R] = new QComboBox{this};

  // Default property labels
  layout->addWidget(new QLabel{"x", this}, 0, 0);
  layout->addWidget(new QLabel{"y", this}, 1, 0);
  layout->addWidget(new QLabel{"z", this}, 2, 0);
  layout->addWidget(new QLabel{"Vx", this}, 3, 0);
  layout->addWidget(new QLabel{"Vy", this}, 4, 0);
  layout->addWidget(new QLabel{"Vz", this}, 5, 0);
  layout->addWidget(new QLabel{"Radio", this}, 6, 0);
  // Default property seletors
  layout->addWidget(selectors[StoryLoader::DefaultProperty::X], 0, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::Y], 1, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::Z], 2, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::VX], 3, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::VY], 4, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::VZ], 5, 1);
  layout->addWidget(selectors[StoryLoader::DefaultProperty::R], 6, 1);

  setCount(0);
}

void StoryLoaderPropertyGrid::setCount(int count)
{
  for (auto [_, selector] : selectors)
  {
    auto value = selector->currentData().toInt();
    selector->clear();
    selector->addItem("N/A", -1);
    for (int i = 1; i <= count; i++)
    {
      selector->addItem(std::to_string(i).c_str(), i - 1);
    }
    selector->setCurrentIndex(value >= count ? 0 : value + 1);
  }
}

std::map<StoryLoader::DefaultProperty, int> StoryLoaderPropertyGrid::getDefaultProperties() const
{
  auto values = std::map<StoryLoader::DefaultProperty, int>{};
  for (auto [property, selector] : selectors)
  {
    auto text = selector->currentText();
    values[property] = text != "N/A" ? text.toInt() - 1 : -1;
  }
  return values;
}