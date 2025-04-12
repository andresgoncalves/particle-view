#include "StoryLoaderPropertyRow.h"

#include <map>

#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

StoryLoaderPropertyRow::StoryLoaderPropertyRow(const char *title, QWidget *parent) : StoryLoaderPropertyRow{title, false, parent} {}

StoryLoaderPropertyRow::StoryLoaderPropertyRow(const char *title, bool canDelete, QWidget *parent) : QWidget{parent}
{

  auto label = new QLabel{title, this};

  comboBox = new QComboBox{this};

  auto layout = new QGridLayout{this};
  layout->addWidget(label, 0, 0);
  layout->addWidget(comboBox, 0, 1);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 0);
  layout->setColumnMinimumWidth(2, 64);
  layout->setHorizontalSpacing(8);

  if (canDelete)
  {
    deleteButton = new QPushButton{"X", this};
    layout->addWidget(deleteButton, 0, 2);
  }
  else
  {
    layout->addWidget(new QWidget{this}, 0, 2);
  }
}

void StoryLoaderPropertyRow::setCount(int count)
{
  auto data = comboBox->currentData();
  auto value = data.isValid() ? data.toInt() : -1;

  comboBox->clear();
  comboBox->addItem("N/A", -1);

  for (int i = 1; i <= count; i++)
    comboBox->addItem(std::to_string(i).c_str(), i - 1);

  comboBox->setCurrentIndex(value >= count ? 0 : value + 1);
}

QComboBox *StoryLoaderPropertyRow::getComboBox() const
{
  return comboBox;
};

QPushButton *StoryLoaderPropertyRow::getDeleteButton() const
{
  return deleteButton;
};