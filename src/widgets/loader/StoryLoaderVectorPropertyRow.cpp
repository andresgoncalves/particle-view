#include "StoryLoaderVectorPropertyRow.h"

#include <map>

#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

StoryLoaderVectorPropertyRow::StoryLoaderVectorPropertyRow(const char *title, QWidget *parent) : StoryLoaderVectorPropertyRow{title, false, parent} {}

StoryLoaderVectorPropertyRow::StoryLoaderVectorPropertyRow(const char *title, bool canDelete, QWidget *parent) : StoryLoaderPropertyRow{title, canDelete, parent}
{
  comboBoxes = {
      new QComboBox{this},
      new QComboBox{this},
      new QComboBox{this},
  };

  auto widget = new QWidget{this};

  auto comboBoxLayout = new QVBoxLayout{widget};
  comboBoxLayout->addWidget(comboBoxes[0]);
  comboBoxLayout->addWidget(comboBoxes[1]);
  comboBoxLayout->addWidget(comboBoxes[2]);
  comboBoxLayout->setContentsMargins({});

  setWidget(widget);
}

void StoryLoaderVectorPropertyRow::setCount(int count)
{
  for (int i = 0; i < 3; i++)
  {
    auto data = comboBoxes[i]->currentData();
    auto value = data.isValid() ? data.toInt() : -1;

    comboBoxes[i]->clear();
    comboBoxes[i]->addItem("N/A", -1);

    for (int j = 1; j <= count; j++)
      comboBoxes[i]->addItem(std::to_string(j).c_str(), j - 1);

    comboBoxes[i]->setCurrentIndex(value >= count ? 0 : value + 1);
  }
}

std::array<int, 3> StoryLoaderVectorPropertyRow::getValues() const
{
  return {
      comboBoxes[0]->currentData().toInt(),
      comboBoxes[1]->currentData().toInt(),
      comboBoxes[2]->currentData().toInt(),
  };
};