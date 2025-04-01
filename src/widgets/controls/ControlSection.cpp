#include "ControlSection.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

ControlSection::ControlSection(const char *title, QWidget *parent) : QWidget{parent}
{
  label = new QLabel{title, this};
  content = new QWidget{this};
  label->setContentsMargins(2, 2, 2, 0);

  auto layout = new QVBoxLayout{this};
  layout->addWidget(label);
  layout->addWidget(content);
  layout->setContentsMargins(8, 4, 8, 4);
}

QWidget *ControlSection::getContent()
{
  return content;
}