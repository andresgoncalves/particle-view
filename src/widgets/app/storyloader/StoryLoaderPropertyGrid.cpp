#include "StoryLoaderPropertyGrid.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>

#include "StoryLoaderAddPropertyDialog.h"
#include "StoryLoaderScalarPropertyRow.h"
#include "StoryLoaderVectorPropertyRow.h"
#include "StoryLoaderStringPropertyRow.h"

StoryLoaderPropertyGrid::StoryLoaderPropertyGrid(QWidget *parent) : QWidget{parent}
{
  auto addPropertyButton = new QPushButton{"Agregar propiedad", this};
  auto addPropertyCallback = [=, this]
  {
    auto addPropertyDialog = new StoryLoaderAddPropertyDialog{this};
    if (addPropertyDialog->exec() == QDialog::Accepted)
    {
      addProperty(addPropertyDialog->getProperty(), addPropertyDialog->getType());
    }
    addPropertyDialog->deleteLater();
  };
  connect(addPropertyButton, &QPushButton::clicked, this, addPropertyCallback);

  auto scrollArea = new QScrollArea{this};
  scrollArea->setWidget(new QWidget{this});
  scrollArea->setWidgetResizable(true);
  scrollArea->setFrameStyle(0);
  scrollArea->setMaximumHeight(640);

  itemLayout = new QVBoxLayout{scrollArea->widget()};
  itemLayout->setAlignment(Qt::AlignTop);
  for (auto [_, row] : propertyRows)
    itemLayout->addWidget(row);

  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(8, 4, 8, 4);
  layout->addWidget(scrollArea);
  layout->addWidget(addPropertyButton);
}

void StoryLoaderPropertyGrid::setCount(int count)
{
  for (auto [_, row] : propertyRows)
    row->setCount(count);
  this->count = count;
}

std::map<std::string, StoryLoader::PropertyDefinition> StoryLoaderPropertyGrid::getProperties() const
{
  auto values = std::map<std::string, StoryLoader::PropertyDefinition>{};

  for (auto [propertyName, row] : propertyRows)
  {
    if (auto scalarRow = dynamic_cast<StoryLoaderScalarPropertyRow *>(row))
      values[propertyName] = {PropertyType::Scalar, scalarRow->getValue()};
    else if (auto vectorRow = dynamic_cast<StoryLoaderVectorPropertyRow *>(row))
      values[propertyName] = {PropertyType::Vector, vectorRow->getValues()};
    else if (auto stringRow = dynamic_cast<StoryLoaderStringPropertyRow *>(row))
      values[propertyName] = {PropertyType::String, stringRow->getValue()};
  }

  return values;
}
void StoryLoaderPropertyGrid::addProperty(std::string property, PropertyType type, bool editable)
{
  if (propertyRows.find(property) != propertyRows.end())
  {
    QMessageBox{QMessageBox::Icon::NoIcon, "Error", "Ya declaraste esta propiedad"}.exec();
    return;
  }

  StoryLoaderPropertyRow *row = nullptr;
  switch (type)
  {
  case PropertyType::Scalar:
    row = new StoryLoaderScalarPropertyRow{property.c_str(), editable, this};
    propertyRows[property] = row;
    break;
  case PropertyType::Vector:
    row = new StoryLoaderVectorPropertyRow{property.c_str(), editable, this};
    propertyRows[property] = row;
    break;
  case PropertyType::String:
    row = new StoryLoaderStringPropertyRow{property.c_str(), editable, this};
    propertyRows[property] = row;
    break;
  }
  row->setCount(count);

  // TODO: if editable
  if (editable)
  {
    auto actionMenu = new QMenu{this};
    auto deleteAction = actionMenu->addAction("Eliminar");
    connect(deleteAction, &QAction::triggered,
            [=, this]()
            { removeProperty(property); });

    auto actionsButton = row->getActionsButton();
    connect(actionsButton, &QPushButton::clicked,
            [=, this]()
            { actionMenu->popup(mapToGlobal(actionsButton->pos() + QPoint{0, actionsButton->height()})); });
  }
  itemLayout->addWidget(row);
}

void StoryLoaderPropertyGrid::removeProperty(std::string property)
{
  auto row = propertyRows.find(property);
  if (row != propertyRows.end())
  {
    itemLayout->removeWidget(row->second);
    row->second->deleteLater();
    propertyRows.erase(row);
  }
}
