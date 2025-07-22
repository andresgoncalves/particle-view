#include "ColorDialog.h"

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include <widgets/shared/controls/Control.h>
#include <utils/color/SolidColorStrategy.h>
#include <utils/color/ColorScaleStrategy.h>

ColorDialog::ColorDialog(AppContext &appContext, QWidget *parent) : appContext{appContext}, QDialog{parent}
{
  // Control variants
  solidColorControls = new SolidColorControl{appContext, this};
  colorScaleControls = new ColorScaleControl{appContext, this};

  // Stacked widget
  auto stackedColorControls = new QStackedWidget{this};
  stackedColorControls->addWidget(solidColorControls);
  stackedColorControls->addWidget(colorScaleControls);

  // Color strategy control
  colorStrategyComboBox = new QComboBox{this};
  colorStrategyComboBox->addItems({"Color único", "Escala de colores"});
  connect(colorStrategyComboBox, &QComboBox::currentIndexChanged, this,
          [=](int index)
          {
            stackedColorControls->setCurrentIndex(index);
          });
  auto colorStrategyControl = new Control<QComboBox>{"Modo de color", colorStrategyComboBox, this};

  // Set buttons
  auto acceptButton = new QPushButton{"Aplicar", this};
  auto cancelButton = new QPushButton{"Cancelar", this};
  auto buttonBox = new QDialogButtonBox{this};
  buttonBox->addButton(acceptButton, QDialogButtonBox::AcceptRole);
  buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);
  connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

  // Build layout
  auto layout = new QVBoxLayout{this};
  layout->addWidget(colorStrategyControl);
  layout->addWidget(stackedColorControls);
  layout->addWidget(buttonBox);
}

void ColorDialog::setColorStrategy(ColorStrategy *colorStrategy) const
{
  // Set control variant
  if (auto solidColorStrategy = dynamic_cast<SolidColorStrategy *>(colorStrategy))
  {
    solidColorControls->setColorStrategy(solidColorStrategy);
    colorStrategyComboBox->setCurrentIndex(0);
  }
  else if (auto colorScaleStrategy = dynamic_cast<ColorScaleStrategy *>(colorStrategy))
  {
    colorScaleControls->setColorStrategy(colorScaleStrategy);
    colorStrategyComboBox->setCurrentIndex(1);
  }
}

std::shared_ptr<ColorStrategy> ColorDialog::getColorStrategy() const
{
  switch (colorStrategyComboBox->currentIndex())
  {
  case 0:
    return solidColorControls->getColorStrategy();
  case 1:
    return colorScaleControls->getColorStrategy();
  }
  return std::make_shared<SolidColorStrategy>(QColor{0, 0, 0});
}
