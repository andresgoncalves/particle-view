#ifndef TEXT_CONTROL_H
#define TEXT_CONTROL_H

#include <string>
#include <functional>

#include <QtWidgets/QLineEdit>

#include "Control.h"

/** Text control with title and a line edit */
class TextControl : public Control<QLineEdit>
{
public:
  /** Creates a vertical control without title */
  TextControl(QWidget *parent = nullptr);
  /** Creates a vertical control with title */
  TextControl(const char *title, QWidget *parent = nullptr);
  /** Creates a control with title and given direction */
  TextControl(const char *title, QBoxLayout::Direction direction, QWidget *parent = nullptr);

  /** Get line edit */
  QLineEdit *getLineEdit() const;

  /** Set control value */
  void setValue(std::string value);

  /** Get control value */
  std::string getValue() const;

  /** Add change listener */
  void onChange(std::function<void(std::string)> callback) const;
};

#endif