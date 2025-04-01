#include "RotationViewControls.h"

#include <QtWidgets/QHBoxLayout>

RotationViewControls::RotationViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Rotación", parent}
{

  xRotationControl = new NumericControl{"x:", this};
  connect(xRotationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setRotationX(xRotationControl->getLineEdit()->text().toFloat()); });
  yRotationControl = new NumericControl{"y':", this};
  connect(yRotationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setRotationY(yRotationControl->getLineEdit()->text().toFloat()); });
  zRotationControl = new NumericControl{"z\":", this};
  connect(zRotationControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setRotationZ(zRotationControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(xRotationControl);
  layout->addWidget(yRotationControl);
  layout->addWidget(zRotationControl);
  layout->setContentsMargins({});

  auto rotationCallback = [&](QVector3D value)
  {
    xRotationControl->getLineEdit()->setText(QString::number(value.x(), 'f', 3));
    yRotationControl->getLineEdit()->setText(QString::number(value.y(), 'f', 3));
    zRotationControl->getLineEdit()->setText(QString::number(value.z(), 'f', 3));
  };

  rotationCallback(appContext.viewController.rotationObservable.get());

  appContext.viewController.rotationObservable.subscribe(this, rotationCallback);
}

RotationViewControls::~RotationViewControls()
{
  appContext.viewController.rotationObservable.unsubscribe(this);
}