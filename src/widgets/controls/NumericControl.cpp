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
void NumericControl::onChange<int>(std::function<void(int)> callback) const
{
  connect(lineEdit, &QLineEdit::editingFinished, this, [&, callback = callback]
          { callback(lineEdit->text().toInt()); });
}

template <>
void NumericControl::onChange<float>(std::function<void(float)> callback) const
{
  connect(lineEdit, &QLineEdit::editingFinished, this, [&, callback = callback]
          { callback(lineEdit->text().toFloat()); });
}

template <>
void NumericControl::onChange<double>(std::function<void(double)> callback) const
{
  connect(lineEdit, &QLineEdit::editingFinished, this, [&, callback = callback]
          { callback(lineEdit->text().toDouble()); });
}