#include "ColorControl.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

ColorControl::ColorControl(QWidget *parent) : ColorControl{nullptr, parent} {}

ColorControl::ColorControl(const char *title, QWidget *parent) : ColorControl{title, false, parent} {}

ColorControl::ColorControl(const char *title, bool withCheckBox, QWidget *parent) : QWidget{parent}
{
  // Create layout
  auto layout = new QHBoxLayout{this};
  layout->setContentsMargins({});

  // Add checkbox
  checkBox = new QCheckBox{this};
  if (withCheckBox)
  {
    checkBox->setContentsMargins({});
    layout->addWidget(checkBox);
  }
  else
  {
    checkBox->hide();
  }

  // Add title
  if (title != nullptr)
  {
    auto label = new QLabel{title, this};
    label->setContentsMargins(4, 0, 4, 0);
    layout->addWidget(label);
  }

  // Push color the right
  if (withCheckBox || title != nullptr)
    layout->addStretch();

  // Add color button
  colorButton = new ColorButton{this};
  layout->addWidget(colorButton);
}

QCheckBox *ColorControl::getCheckBox() const
{
  return checkBox;
}

ColorButton *ColorControl::getColorButton() const
{
  return colorButton;
}