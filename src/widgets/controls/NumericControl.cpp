#include "NumericControl.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

NumericControl::NumericControl(QWidget *parent) : NumericControl{nullptr, parent} {}

NumericControl::NumericControl(const char *title, QWidget *parent) : QWidget{parent}
{
  lineEdit = new QLineEdit{this};

  layout = new QBoxLayout{QBoxLayout::Direction::TopToBottom, this};
  if (title != nullptr)
  {
    label = new QLabel{title, this};
    layout->addWidget(label);
  }
  layout->addWidget(lineEdit);
  layout->setContentsMargins({});
}

QLineEdit *NumericControl::getLineEdit() const
{
  return lineEdit;
}

QBoxLayout *NumericControl::getLayout() const
{
  return layout;
}

void NumericControl::setValue(int value)
{
  lineEdit->setText(QString::number(value));
}

void NumericControl::setValue(float value)
{
  lineEdit->setText(QString::number(value, 'f', 3));
}

void NumericControl::setValue(double value)
{
  lineEdit->setText(QString::number(value, 'f', 3));
}

template <>
int NumericControl::getValue<int>() const
{
  return lineEdit->text().toInt();
}

template <>
float NumericControl::getValue<float>() const
{
  return lineEdit->text().toFloat();
}

template <>
double NumericControl::getValue<double>() const
{
  return lineEdit->text().toDouble();
}