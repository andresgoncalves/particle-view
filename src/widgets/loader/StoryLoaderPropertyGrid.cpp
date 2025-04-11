#include "StoryLoaderPropertyGrid.h"

#include <map>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

StoryLoaderPropertyGrid::StoryLoaderPropertyGrid(QWidget *parent) : QWidget{parent}
{
  auto layout = new QGridLayout{this};

  selectors[CustomLoader::DefaultProperty::X] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::Y] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::Z] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::VX] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::VY] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::VZ] = new QComboBox{this};
  selectors[CustomLoader::DefaultProperty::R] = new QComboBox{this};

  // Default property labels
  layout->addWidget(new QLabel{"x", this}, 0, 0);
  layout->addWidget(new QLabel{"y", this}, 1, 0);
  layout->addWidget(new QLabel{"z", this}, 2, 0);
  layout->addWidget(new QLabel{"Vx", this}, 3, 0);
  layout->addWidget(new QLabel{"Vy", this}, 4, 0);
  layout->addWidget(new QLabel{"Vz", this}, 5, 0);
  layout->addWidget(new QLabel{"Radio", this}, 6, 0);
  // Default property seletors
  layout->addWidget(selectors[CustomLoader::DefaultProperty::X], 0, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::Y], 1, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::Z], 2, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::VX], 3, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::VY], 4, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::VZ], 5, 1);
  layout->addWidget(selectors[CustomLoader::DefaultProperty::R], 6, 1);

  setCount(0);
}

void StoryLoaderPropertyGrid::setCount(int count)
{
  for (auto [_, selector] : selectors)
  {
    selector->clear();
    selector->addItem("N/A");
    for (int i = 1; i <= count; i++)
    {
      selector->addItem(std::to_string(i).c_str());
    }
  }
}

std::map<CustomLoader::DefaultProperty, int> StoryLoaderPropertyGrid::getDefaultProperties() const
{
  auto values = std::map<CustomLoader::DefaultProperty, int>{};
  for (auto [property, selector] : selectors)
  {
    auto text = selector->currentText();
    values[property] = text != "N/A" ? text.toInt() - 1 : -1;
  }
  return values;
}