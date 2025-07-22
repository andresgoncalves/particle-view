#include "SolidColorControl.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/dialogs/ColorPicker.h>
#include <utils/color/SolidColorStrategy.h>

SolidColorControl::SolidColorControl(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  // Color control
  colorControl = new ColorControl{"Color", false, this};
  connect(colorControl->getColorButton(), &ColorButton::clicked, this,
          [this]
          {
            auto pickedColor = ColorPicker::getColor(solidColor, this);
            if (pickedColor.has_value())
            {
              solidColor = pickedColor.value();
              colorControl->getColorButton()->setSolidColor(solidColor);
            }
          });

  // Build layout
  auto layout = new QVBoxLayout{this};
  layout->addWidget(colorControl);
  layout->setAlignment(Qt::AlignTop);
  layout->setContentsMargins({});
}

void SolidColorControl::setColorStrategy(SolidColorStrategy *colorStrategy)
{
  solidColor = colorStrategy->getSolidColor();
  colorControl->getColorButton()->setSolidColor(solidColor);
}

std::shared_ptr<SolidColorStrategy> SolidColorControl::getColorStrategy() const
{
  return std::make_shared<SolidColorStrategy>(solidColor);
}
