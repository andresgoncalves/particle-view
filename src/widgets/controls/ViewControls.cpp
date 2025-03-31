#include "ViewControls.h"

#include <QtWidgets/QHBoxLayout>

ViewControls::ViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Vista", parent}
{

  xTranslationControl = new NumericControl{"x:", this};
  connect(xTranslationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setTranslationX(xTranslationControl->getLineEdit()->text().toFloat()); });
  yTranslationControl = new NumericControl{"y:", this};
  connect(yTranslationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setTranslationY(yTranslationControl->getLineEdit()->text().toFloat()); });
  zTranslationControl = new NumericControl{"z:", this};
  connect(zTranslationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setTranslationZ(zTranslationControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};

  layout->addWidget(xTranslationControl);
  layout->addWidget(yTranslationControl);
  layout->addWidget(zTranslationControl);

  auto translationCallback = [&](QVector3D value)
  {
    xTranslationControl->getLineEdit()->setText(QString::number(value.x(), 'f', 3));
    yTranslationControl->getLineEdit()->setText(QString::number(value.y(), 'f', 3));
    zTranslationControl->getLineEdit()->setText(QString::number(value.z(), 'f', 3));
  };

  translationCallback(appContext.viewController.translationObservable.get());

  appContext.viewController.translationObservable.subscribe(this, translationCallback);
}

ViewControls::~ViewControls()
{
  appContext.viewController.translationObservable.unsubscribe(this);
}