#include "NumericControl.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

NumericControl::NumericControl(QWidget *parent) : NumericControl{nullptr, parent} {}

NumericControl::NumericControl(const char *title, QWidget *parent) : QWidget{parent}
{
  lineEdit = new QLineEdit{this};

  auto layout = new QVBoxLayout{this};
  if (title != nullptr)
  {
    label = new QLabel{title, this};
    layout->addWidget(label);
  }
  layout->addWidget(lineEdit);
  layout->setContentsMargins({});
}

QLineEdit *NumericControl::getLineEdit()
{
  return lineEdit;
}