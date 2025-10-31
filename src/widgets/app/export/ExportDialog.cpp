#include "ExportDialog.h"

#include <fstream>
#include <filesystem>

#include <QtWidgets/QtWidgets>

ExportDialog::ExportDialog(AppContext &appContext, QWidget *parent) : appContext{appContext}, QDialog{parent}
{
  setWindowTitle("Exportar animación");

  animationSpeedControl = new NumericControl("Velocidad de animación", this);
  animationSpeedControl->setValue(appContext.animationController.getAnimationSpeed());

  framesPerSecondControl = new NumericControl("Cuadros por segundo", this);

  auto controlsLayout = new QVBoxLayout{};
  controlsLayout->setContentsMargins(8, 4, 8, 4);
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
