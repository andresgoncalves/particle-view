#include "ScaleViewControls.h"

#include <QtWidgets/QHBoxLayout>

ScaleViewControls::ScaleViewControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Escala", parent}
{

  scaleControl = new NumericControl{this};
  connect(scaleControl->getLineEdit(), &QLineEdit::editingFinished, this, [&]
          { appContext.viewController.setScale(scaleControl->getLineEdit()->text().toFloat()); });

  auto layout = new QHBoxLayout{content};
  layout->addWidget(scaleControl);
  layout->setContentsMargins({});

  auto scaleCallback = [&](float value)
  {
    scaleControl->getLineEdit()->setText(QString::number(value, 'f', 3));
  };

  scaleCallback(appContext.viewController.scaleObservable.get());

  appContext.viewController.scaleObservable.subscribe(this, scaleCallback);
}

ScaleViewControls::~ScaleViewControls()
{
  appContext.viewController.scaleObservable.unsubscribe(this);
}