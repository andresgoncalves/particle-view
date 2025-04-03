#ifndef NUMERIC_CONTROL_H
#define NUMERIC_CONTROL_H

#include <functional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

#include "../../controllers/Observable.h"

class NumericControl : public QWidget
{
public:
  NumericControl(QWidget *parent);
  NumericControl(const char *title, QWidget *parent);

  QLineEdit *getLineEdit() const;

  void setValue(int value);
  void setValue(float value);
  void setValue(double value);

  template <typename T>
  void onChange(std::function<void(T)> callback) const;

protected:
  QLabel *label = nullptr;
  QLineEdit *lineEdit = nullptr;
};

#endif