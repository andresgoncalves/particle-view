#include "ExportDialog.h"

#include <fstream>
#include <filesystem>

#include <QtWidgets/QtWidgets>

ExportDialog::ExportDialog(AppContext &appContext, QWidget *parent) : appContext{appContext}, QDialog{parent}
{
  setWindowTitle("Exportar animación");

  widthControl = new NumericControl("Ancho", this);
  widthControl->setValue(1280);

  heightControl = new NumericControl("Alto", this);
  heightControl->setValue(720);

  auto sizeLayout = new QHBoxLayout{};
  sizeLayout->setContentsMargins(0, 4, 0, 4);
  sizeLayout->addWidget(widthControl);
  sizeLayout->addWidget(heightControl);

  animationSpeedControl = new NumericControl("Velocidad de animación", this);
  animationSpeedControl->setValue(appContext.animationController.getAnimationSpeed());

  framesPerSecondControl = new NumericControl("Cuadros por segundo", this);
  framesPerSecondControl->setValue(1);

  auto controlsLayout = new QVBoxLayout{};
  controlsLayout->setContentsMargins(8, 4, 8, 4);
  controlsLayout->addLayout(sizeLayout);
  controlsLayout->addWidget(animationSpeedControl);
  controlsLayout->addWidget(framesPerSecondControl);

  auto loadButton = new QPushButton{"Exportar", this};
  connect(loadButton, &QPushButton::clicked, this, &QDialog::accept);

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setContentsMargins(8, 4, 8, 4);
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(loadButton);

  auto verticalLayout = new QVBoxLayout{this};
  verticalLayout->setContentsMargins(0, 4, 0, 4);
  verticalLayout->addLayout(controlsLayout);
  verticalLayout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

float ExportDialog::getAnimationSpeed() const
{
  return animationSpeedControl->getValue<float>();
}

int ExportDialog::getFramesPerSecond() const
{
  return framesPerSecondControl->getValue<int>();
}

QSize ExportDialog::getSize() const
{
  return {widthControl->getValue<int>(), heightControl->getValue<int>()};
}