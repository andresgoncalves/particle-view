#include "DisplayColorControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

DisplayColorControls::DisplayColorControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Colores", parent}
{
  auto defaultColorTextField = new QLineEdit{this};
  defaultColorTextField->setText(appContext.displayController.getDefaultColor().name());
  auto defaultColorLabel = new QLabel{"Partícula", this};
  auto defaultColorButton = new QPushButton{"Seleccionar", this};
  auto defaultColorButtonCallback = [=, &appContext, this]
  {
    auto color = QColor{defaultColorTextField->text()};
    auto colorDialog = new QColorDialog{color, this};
    colorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    if (colorDialog->exec() == QDialog::Accepted)
    {
      appContext.displayController.setDefaultColor(colorDialog->currentColor().name());
    }
    colorDialog->deleteLater();
  };
  connect(defaultColorButton, &QPushButton::clicked, this, defaultColorButtonCallback);

  auto defaultColorLayout = new QHBoxLayout{};
  defaultColorLayout->setAlignment(Qt::AlignVCenter);
  defaultColorLayout->addWidget(defaultColorLabel);
  defaultColorLayout->addWidget(defaultColorTextField);
  defaultColorLayout->addWidget(defaultColorButton);

  auto backgroundColorTextField = new QLineEdit{this};
  backgroundColorTextField->setText(appContext.displayController.getBackgroundColor().name());
  auto backgroundColorLabel = new QLabel{"Fondo", this};
  auto backgroundColorButton = new QPushButton{"Seleccionar", this};
  auto backgroundColorButtonCallback = [=, &appContext, this]
  {
    auto color = QColor{backgroundColorTextField->text()};
    auto colorDialog = new QColorDialog{color, this};
    if (colorDialog->exec() == QDialog::Accepted)
    {
      appContext.displayController.setBackgroundColor(colorDialog->currentColor().name());
    }
    colorDialog->deleteLater();
  };
  connect(backgroundColorButton, &QPushButton::clicked, this, backgroundColorButtonCallback);

  auto backgroundColorLayout = new QHBoxLayout{};
  backgroundColorLayout->setAlignment(Qt::AlignVCenter);
  backgroundColorLayout->addWidget(backgroundColorLabel);
  backgroundColorLayout->addWidget(backgroundColorTextField);
  backgroundColorLayout->addWidget(backgroundColorButton);

  auto layout = new QVBoxLayout{content};
  layout->addLayout(defaultColorLayout);
  layout->addLayout(backgroundColorLayout);
  layout->setContentsMargins({});

  appContext.displayController.defaultColorObservable.subscribe(this, [=](QColor color)
                                                                { defaultColorTextField->setText(color.name()); });
  appContext.displayController.backgroundColorObservable.subscribe(this, [=](QColor color)
                                                                   { backgroundColorTextField->setText(color.name()); });
}

DisplayColorControls::~DisplayColorControls()
{
  appContext.displayController.defaultColorObservable.unsubscribe(this);
  appContext.displayController.backgroundColorObservable.unsubscribe(this);
}