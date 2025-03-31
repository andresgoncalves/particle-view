#include "NumericControl.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

NumericControl::NumericControl(const char *title, QWidget *parent) : QWidget{parent}
{
  titleLabel = new QLabel{title, this};
  lineEdit = new QLineEdit{this};

  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(titleLabel);
  layout->addWidget(lineEdit);
}

QLineEdit *NumericControl::getLineEdit()
{
  return lineEdit;
}