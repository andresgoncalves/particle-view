#include "TextControl.h"

TextControl::TextControl(QWidget *parent) : TextControl{nullptr, parent} {}

TextControl::TextControl(const char *title, QWidget *parent) : TextControl{title, QBoxLayout::Direction::Down, parent} {}

TextControl::TextControl(const char *title, QBoxLayout::Direction direction, QWidget *parent) : Control{title, new QLineEdit{}, direction, parent} {}

QLineEdit *TextControl::getLineEdit() const
{
  return widget;
}

void TextControl::setValue(std::string value)
{
  widget->setText(value.c_str());
}

std::string TextControl::getValue() const
{
  return widget->text().toStdString();
}

void TextControl::onChange(std::function<void(std::string)> callback) const
{
  connect(widget, &QLineEdit::editingFinished, this, [&, callback]
          { callback(getValue()); });
};