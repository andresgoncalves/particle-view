#ifndef NUMERIC_CONTROL_H
#define NUMERIC_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class NumericControl : public QWidget
{
public:
  NumericControl(const char *title, QWidget *parent);

  QLineEdit *getLineEdit();

protected:
  QLabel *titleLabel = nullptr;
  QLineEdit *lineEdit = nullptr;
};

#endif