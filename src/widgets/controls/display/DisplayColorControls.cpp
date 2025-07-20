#include "DisplayColorControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>

#include "DisplayColorRuleDialog.h"

DisplayColorControls::DisplayColorControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Colores", parent}
{
  auto particleColorLabel = new QLabel{"Partícula", this};
  auto particleColorButton = new QPushButton{"Seleccionar", this};
  auto particleColorButtonCallback = [=, &appContext, this]
  {
    auto colorDialog = new DisplayColorRuleDialog{appContext.displayController.getParticleColorRule(), appContext, parent};
    if (colorDialog->exec() == QDialog::Accepted)
    {
      appContext.displayController.setParticleColorRule(colorDialog->getColorRule());
    }
    colorDialog->deleteLater();
  };
  connect(particleColorButton, &QPushButton::clicked, this, particleColorButtonCallback);

  auto particleColorLayout = new QHBoxLayout{};
  particleColorLayout->setAlignment(Qt::AlignVCenter);
  particleColorLayout->addWidget(particleColorLabel);
  particleColorLayout->addWidget(particleColorButton);

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
  layout->addLayout(particleColorLayout);
  layout->addLayout(backgroundColorLayout);
  layout->setContentsMargins({});

  appContext.displayController.backgroundColorObservable.subscribe(this, [=](QColor color)
                                                                   { backgroundColorTextField->setText(color.name()); });
}

DisplayColorControls::~DisplayColorControls()
{
  appContext.displayController.backgroundColorObservable.unsubscribe(this);
}