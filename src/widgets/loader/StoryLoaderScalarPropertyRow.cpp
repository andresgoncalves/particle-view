#include "StoryLoaderScalarPropertyRow.h"

#include <map>

#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

StoryLoaderScalarPropertyRow::StoryLoaderScalarPropertyRow(const char *title, QWidget *parent) : StoryLoaderScalarPropertyRow{title, false, parent} {}

StoryLoaderScalarPropertyRow::StoryLoaderScalarPropertyRow(const char *title, bool canDelete, QWidget *parent) : StoryLoaderPropertyRow{title, canDelete, parent}
{
  comboBox = new QComboBox{this};
  setWidget(comboBox);
}

void StoryLoaderScalarPropertyRow::setCount(int count)
{
  auto data = comboBox->currentData();
  auto value = data.isValid() ? data.toInt() : -1;

  comboBox->clear();
  comboBox->addItem("N/A", -1);

  for (int i = 1; i <= count; i++)
    comboBox->addItem(std::to_string(i).c_str(), i - 1);

  comboBox->setCurrentIndex(value >= count ? 0 : value + 1);
}

int StoryLoaderScalarPropertyRow::getValue() const
{
  return comboBox->currentData().toInt();
};