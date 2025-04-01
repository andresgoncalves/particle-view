#include "OriginViewControls.h"

#include <QtWidgets/QHBoxLayout>

OriginViewControls::OriginViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Origen", parent}
{

  xOriginControl = new NumericControl{"x:", this};
  connect(xOriginControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setOriginX(xOriginControl->getLineEdit()->text().toFloat()); });
  yOriginControl = new NumericControl{"y:", this};
  connect(yOriginControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setOriginY(yOriginControl->getLineEdit()->text().toFloat()); });
  zOriginControl = new NumericControl{"z:", this};
  connect(zOriginControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setOriginZ(zOriginControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(xOriginControl);
  layout->addWidget(yOriginControl);
  layout->addWidget(zOriginControl);
  layout->setContentsMargins({});

  auto originCallback = [&](QVector3D value)
  {
    xOriginControl->getLineEdit()->setText(QString::number(value.x(), 'f', 3));
    yOriginControl->getLineEdit()->setText(QString::number(value.y(), 'f', 3));
    zOriginControl->getLineEdit()->setText(QString::number(value.z(), 'f', 3));
  };

  originCallback(appContext.viewController.originObservable.get());

  appContext.viewController.originObservable.subscribe(this, originCallback);
}

OriginViewControls::~OriginViewControls()
{
  appContext.viewController.originObservable.unsubscribe(this);
}