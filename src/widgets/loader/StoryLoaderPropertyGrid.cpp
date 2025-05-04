#include "StoryLoaderPropertyGrid.h"

#include <map>

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>

#include "StoryLoaderAddPropertyDialog.h"

StoryLoaderPropertyGrid::StoryLoaderPropertyGrid(QWidget *parent) : QWidget{parent}
{
  // Default properties
  defaultRows[StoryLoader::DefaultProperty::X] = new StoryLoaderScalarPropertyRow{"x", this};
  defaultRows[StoryLoader::DefaultProperty::Y] = new StoryLoaderScalarPropertyRow{"y", this};
  defaultRows[StoryLoader::DefaultProperty::Z] = new StoryLoaderScalarPropertyRow{"z", this};
  defaultRows[StoryLoader::DefaultProperty::VX] = new StoryLoaderScalarPropertyRow{"Vx", this};
  defaultRows[StoryLoader::DefaultProperty::VY] = new StoryLoaderScalarPropertyRow{"Vy", this};
  defaultRows[StoryLoader::DefaultProperty::VZ] = new StoryLoaderScalarPropertyRow{"Vz", this};
  defaultRows[StoryLoader::DefaultProperty::R] = new StoryLoaderScalarPropertyRow{"Radio", this};

  auto scrollArea = new QScrollArea{this};
  scrollArea->setWidget(new QWidget{this});
  scrollArea->setWidgetResizable(true);
  scrollArea->setFrameStyle(0);
  scrollArea->setMaximumHeight(640);

  itemLayout = new QVBoxLayout{scrollArea->widget()};
  itemLayout->setAlignment(Qt::AlignTop);
  for (auto [_, row] : defaultRows)
    itemLayout->addWidget(row);

  auto layout = new QVBoxLayout{this};
  layout->addWidget(scrollArea);

  setCount(0);
}

void StoryLoaderPropertyGrid::setCount(int count)
{
  for (auto [_, row] : defaultRows)
    row->setCount(count);
  for (auto [_, row] : scalarRows)
    row->setCount(count);

  this->count = count;
}

std::map<StoryLoader::DefaultProperty, int> StoryLoaderPropertyGrid::getDefaultProperties() const
{
  auto values = std::map<StoryLoader::DefaultProperty, int>{};

  for (auto [property, row] : defaultRows)
    values[property] = row->getValue();

  return values;
}

std::map<std::string, int> StoryLoaderPropertyGrid::getScalarProperties() const
{
  auto values = std::map<std::string, int>{};

  for (auto [property, row] : scalarRows)
    values[property] = row->getValue();

  return values;
}

std::map<std::string, std::array<int, 3>> StoryLoaderPropertyGrid::getVectorProperties() const
{
  auto values = std::map<std::string, std::array<int, 3>>{};

  for (auto [property, row] : vectorRows)
    values[property] = row->getValues();

  return values;
};

void StoryLoaderPropertyGrid::addCustomProperty(std::string property, Particle::PropertyType type)
{
  if (scalarRows.find(property) == scalarRows.end() && vectorRows.find(property) == vectorRows.end())
  {
    StoryLoaderPropertyRow *row = nullptr;
    if (type == Particle::PropertyType::Scalar)
    {
      row = new StoryLoaderScalarPropertyRow{property.c_str(), true, this};
      scalarRows[property] = static_cast<StoryLoaderScalarPropertyRow *>(row);
    }
    else
    {
      row = new StoryLoaderVectorPropertyRow{property.c_str(), true, this};
      vectorRows[property] = static_cast<StoryLoaderVectorPropertyRow *>(row);
    }
    row->setCount(count);
    connect(row->getDeleteButton(), &QPushButton::clicked, this, [=, this]
            { removeCustomProperty(property); });

    itemLayout->addWidget(row);
  }
  else
  {
    QMessageBox{QMessageBox::Icon::NoIcon, "Error", "Ya declaraste esta variable"}.exec();
  }
}

void StoryLoaderPropertyGrid::removeCustomProperty(std::string property)
{
  auto scalarRow = scalarRows.find(property);
  if (scalarRow != scalarRows.end())
  {
    itemLayout->removeWidget(scalarRow->second);
    scalarRow->second->deleteLater();
    scalarRows.erase(scalarRow);
  }

  auto vectorRow = vectorRows.find(property);
  if (vectorRow != vectorRows.end())
  {
    itemLayout->removeWidget(vectorRow->second);
    vectorRow->second->deleteLater();
    vectorRows.erase(vectorRow);
  }
}
