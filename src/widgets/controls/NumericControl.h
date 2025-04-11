#ifndef NUMERIC_CONTROL_H
#define NUMERIC_CONTROL_H

#include <functional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QBoxLayout>

#include "../../controllers/Observable.h"

class NumericControl : public QWidget
{
public:
  NumericControl(QWidget *parent = nullptr);
  NumericControl(const char *title, QWidget *parent = nullptr);

  QLineEdit *getLineEdit() const;
  QBoxLayout *getLayout() const;

  void setValue(int value);
  void setValue(float value);
  void setValue(double value);

  template <typename T>
  void onChange(std::function<void(T)> callback) const;

protected:
  QLabel *label;
  QLineEdit *lineEdit;
  QBoxLayout *layout;
};

#endif