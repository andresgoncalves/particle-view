#ifndef NUMERIC_CONTROL_H
#define NUMERIC_CONTROL_H

#include <functional>

#include <QtWidgets/QLineEdit>

#include "Control.h"

/** Numeric control with title and a line edit */
class NumericControl : public Control<QLineEdit>
{
public:
  /** Creates a vertical control without title */
  NumericControl(QWidget *parent = nullptr);
  /** Creates a vertical control with title */
  NumericControl(const char *title, QWidget *parent = nullptr);
  /** Creates a control with title and given direction */
  NumericControl(const char *title, QBoxLayout::Direction direction, QWidget *parent = nullptr);

  /** Get line edit */
  QLineEdit *getLineEdit() const;

  /** Set control value */
  void setValue(int value);
  /** Set control value */
  void setValue(float value);
  /** Set control value */
  void setValue(double value);

  /** Get control value */
  template <typename T>
  T getValue() const;

  /** Add change listener */
  template <typename T>
  void onChange(std::function<void(T)> callback) const
  {
    connect(widget, &QLineEdit::editingFinished, this, [&, callback]
            { callback(getValue<T>()); });
  };
};

#endif