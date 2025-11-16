#include "StoryLoaderVectorPropertyRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

StoryLoaderVectorPropertyRow::StoryLoaderVectorPropertyRow(const char *title, QWidget *parent) : StoryLoaderVectorPropertyRow{title, false, parent} {}

StoryLoaderVectorPropertyRow::StoryLoaderVectorPropertyRow(const char *title, bool canDelete, QWidget *parent) : StoryLoaderPropertyRow{title, canDelete, parent}
{
  controls = {
      new Control{"x:", new QComboBox{this}, QBoxLayout::Direction::LeftToRight},
      new Control{"y:", new QComboBox{this}, QBoxLayout::Direction::LeftToRight},
      new Control{"z:", new QComboBox{this}, QBoxLayout::Direction::LeftToRight},
  };

  auto widget = new QWidget{this};

  auto controlLayout = new QVBoxLayout{widget};
  controlLayout->addWidget(controls[0]);
  controlLayout->addWidget(controls[1]);
  controlLayout->addWidget(controls[2]);
  controlLayout->setSpacing(0);
  controlLayout->setContentsMargins({});

  setWidget(widget);
}

void StoryLoaderVectorPropertyRow::setCount(int count)
{
  for (int i = 0; i < 3; i++)
  {
    auto data = controls[i]->getWidget()->currentData();
    auto value = data.isValid() ? data.toInt() : -1;

    controls[i]->getWidget()->clear();
    controls[i]->getWidget()->addItem("N/A", -1);

    for (int j = 1; j <= count; j++)
      controls[i]->getWidget()->addItem(std::to_string(j).c_str(), j - 1);

    controls[i]->getWidget()->setCurrentIndex(value >= count ? 0 : value + 1);
  }
}

StoryLoader::IndicesType StoryLoaderVectorPropertyRow::getValues() const
{
  return {
      controls[0]->getWidget()->currentData().toUInt(),
      controls[1]->getWidget()->currentData().toUInt(),
      controls[2]->getWidget()->currentData().toUInt(),
  };
};

void StoryLoaderVectorPropertyRow::setVisibleComponents(std::array<bool, 3> components)
{
  for (int i = 0; i < 3; i++)
  {
    controls[i]->setVisible(components[i]);
    // Clear selection
    if (!components[i])
      controls[i]->getWidget()->setCurrentText("N/A");
  }
}
