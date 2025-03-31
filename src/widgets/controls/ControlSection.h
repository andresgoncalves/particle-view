#ifndef CONTROL_SECTION_H
#define CONTROL_SECTION_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class ControlSection : public QWidget
{
public:
  ControlSection(const char *title, QWidget *parent);

  QWidget *getContent();

protected:
  QLabel *titleLabel = nullptr;
  QWidget *content = nullptr;
};

#endif