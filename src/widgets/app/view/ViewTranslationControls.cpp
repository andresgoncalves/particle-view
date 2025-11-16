#include "ViewTranslationControls.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include <widgets/shared/controls/VectorControl.h>

ViewTranslationControls::ViewTranslationControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Traslación", parent}
{
  // Translation control
  auto translationControl = new VectorControl{{"x:", "y:", "z:"}, this};
  translationControl->onChange([&appContext](QVector3D value)
                               { appContext.viewController.setTranslation(value); });
  // Set dimensionality
  auto dimensionalityCallback = [=](ViewController::Dimensionality dimensionality)
  {
    if (dimensionality == ViewController::Dimensionality::Dimension2D)
    {
      translationControl->setVisibleComponents({true, true, false});
    }
    else
    {
      translationControl->setVisibleComponents({true, true, true});
    }
  };
  appContext.viewController.dimensionalityObservable.subscribe(this, dimensionalityCallback, true);

  // Reset button
  auto resetButton = new QPushButton{"Reiniciar", this};
  connect(resetButton, &QPushButton::clicked, this, [&appContext]
          { appContext.viewController.setTranslation({}); });

  auto layout = new QVBoxLayout{content};
  layout->addWidget(translationControl);
  layout->addWidget(resetButton);
  layout->setAlignment(resetButton, Qt::AlignLeft);
  layout->setContentsMargins({});

  // Add translation listener
  auto translationCallback = [=](QVector3D value)
  {
    translationControl->setValue(value);
  };
  appContext.viewController.translationObservable.subscribe(this, translationCallback, true);
}

ViewTranslationControls::~ViewTranslationControls()
{
  appContext.viewController.translationObservable.unsubscribe(this);
}