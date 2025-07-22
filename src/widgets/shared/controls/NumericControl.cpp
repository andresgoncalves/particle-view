#include "NumericControl.h"

NumericControl::NumericControl(QWidget *parent) : NumericControl{nullptr, parent} {}

NumericControl::NumericControl(const char *title, QWidget *parent) : NumericControl{title, QBoxLayout::Direction::Down, parent} {}

NumericControl::NumericControl(const char *title, QBoxLayout::Direction direction, QWidget *parent) : Control{title, new QLineEdit{}, direction, parent} {}

QLineEdit *NumericControl::getLineEdit() const
{
  return widget;
}

void NumericControl::setValue(int value)
{
  widget->setText(QString::number(value));
}

void NumericControl::setValue(float value)
{
  widget->setText(QString::number(value, 'f', 3));
}

void NumericControl::setValue(double value)
{
  widget->setText(QString::number(value, 'f', 3));
}

template <>
int NumericControl::getValue<int>() const
{
  return widget->text().toInt();
}

template <>
float NumericControl::getValue<float>() const
{
  return widget->text().toFloat();
}

template <>
double NumericControl::getValue<double>() const
{
  return widget->text().toDouble();
}