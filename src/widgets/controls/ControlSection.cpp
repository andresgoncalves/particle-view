#include "ControlSection.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

ControlSection::ControlSection(const char *title, QWidget *parent) : QWidget{parent}
{
  titleLabel = new QLabel{title, this};
  content = new QWidget{this};

  auto layout = new QVBoxLayout{this};
  layout->addWidget(titleLabel);
  layout->addWidget(content);
}

QWidget *ControlSection::getContent()
{
  return content;
}