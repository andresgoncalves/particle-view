#include "ViewTranslationControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/NumericControl.h>

ViewTranslationControls::ViewTranslationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Traslación", parent}
{
  // Translation X control
  auto xTranslationControl = new NumericControl{"x:", this};
  xTranslationControl->onChange<float>([&appContext](float value)
                                       { appContext.viewController.setTranslationX(value); });

  // Translation Y control
  auto yTranslationControl = new NumericControl{"y:", this};
  yTranslationControl->onChange<float>([&appContext](float value)
                                       { appContext.viewController.setTranslationY(value); });

  // Translation Z control
  auto zTranslationControl = new NumericControl{"z:", this};
  zTranslationControl->onChange<float>([&appContext](float value)
                                       { appContext.viewController.setTranslationZ(value); });

  // Reset button
  auto resetButton = new QPushButton{"Reiniciar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setTranslation({}); });

  // Build layout
  auto controlLayout = new QHBoxLayout{};
  controlLayout->addWidget(xTranslationControl);
  controlLayout->addWidget(yTranslationControl);
  controlLayout->addWidget(zTranslationControl);
  controlLayout->setContentsMargins({});

  auto layout = new QVBoxLayout{content};
  layout->addLayout(controlLayout);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add translation listener
  auto translationCallback = [=](QVector3D value)
  {
    xTranslationControl->setValue(value.x());
    yTranslationControl->setValue(value.y());
    zTranslationControl->setValue(value.z());
  };
  appContext.viewController.translationObservable.subscribe(this, translationCallback, true);
}

ViewTranslationControls::~ViewTranslationControls()
{
  appContext.viewController.translationObservable.unsubscribe(this);
}