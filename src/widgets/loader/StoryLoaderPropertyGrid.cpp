#include "StoryLoaderPropertyGrid.h"

#include <map>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>

StoryLoaderPropertyGrid::StoryLoaderPropertyGrid(QWidget *parent) : QWidget{parent}
{
  defaultRows[StoryLoader::DefaultProperty::X] = new StoryLoaderPropertyRow{"x", this};
  defaultRows[StoryLoader::DefaultProperty::Y] = new StoryLoaderPropertyRow{"y", this};
  defaultRows[StoryLoader::DefaultProperty::Z] = new StoryLoaderPropertyRow{"z", this};
  defaultRows[StoryLoader::DefaultProperty::VX] = new StoryLoaderPropertyRow{"Vx", this};
  defaultRows[StoryLoader::DefaultProperty::VY] = new StoryLoaderPropertyRow{"Vy", this};
  defaultRows[StoryLoader::DefaultProperty::VZ] = new StoryLoaderPropertyRow{"Vz", this};
  defaultRows[StoryLoader::DefaultProperty::R] = new StoryLoaderPropertyRow{"Radio", this};

  // Default property seletors
  auto scrollArea = new QScrollArea{this};
  scrollArea->setWidget(new QWidget{this});
  scrollArea->setWidgetResizable(true);
  scrollArea->setFrameStyle(0);

  itemLayout = new QVBoxLayout{scrollArea->widget()};
  for (auto [_, row] : defaultRows)
    itemLayout->addWidget(row);

  auto addPropertyTextField = new QLineEdit{this};
  addPropertyTextField->setPlaceholderText("Nueva variable");
  auto addPropertyButton = new QPushButton{"Agregar", this};
  connect(addPropertyButton, &QPushButton::clicked, this, [=, this]
          { addCustomProperty(addPropertyTextField->text().toStdString()); addPropertyTextField->setText(""); });

  auto addPropertyLayout = new QHBoxLayout{};
  addPropertyLayout->addWidget(addPropertyTextField);
  addPropertyLayout->addWidget(addPropertyButton);

  auto layout = new QVBoxLayout{this};
  layout->addWidget(scrollArea);
  layout->addLayout(addPropertyLayout);

  setCount(7);
}

void StoryLoaderPropertyGrid::setCount(int count)
{
  for (auto [_, row] : defaultRows)
    row->setCount(count);
  for (auto [_, row] : customRows)
    row->setCount(count);

  this->count = count;
}

std::map<StoryLoader::DefaultProperty, int> StoryLoaderPropertyGrid::getDefaultProperties() const
{
  auto values = std::map<StoryLoader::DefaultProperty, int>{};

  for (auto [property, row] : defaultRows)
    values[property] = row->getComboBox()->currentData().toInt();

  return values;
}

std::map<std::string, int> StoryLoaderPropertyGrid::getCustomProperties() const
{
  auto values = std::map<std::string, int>{};

  for (auto [property, row] : customRows)
    values[property] = row->getComboBox()->currentData().toInt();

  return values;
}

void StoryLoaderPropertyGrid::addCustomProperty(std::string property)
{
  auto row = customRows.find(property);

  if (row == customRows.end())
  {
    auto row = new StoryLoaderPropertyRow{property.c_str(), true, this};
    row->setCount(count);
    connect(row->getDeleteButton(), &QPushButton::clicked, this, [=, this]
            { removeCustomProperty(property); });

    customRows[property] = row;
    itemLayout->addWidget(row);
  }
  else
  {
    QMessageBox{QMessageBox::Icon::NoIcon, "Error", "Ya declaraste esta variable"}.exec();
  }
}

void StoryLoaderPropertyGrid::removeCustomProperty(std::string property)
{
  auto row = customRows.find(property);

  if (row != customRows.end())
  {
    itemLayout->removeWidget(row->second);
    delete row->second;
    customRows.erase(row);
  }
}
