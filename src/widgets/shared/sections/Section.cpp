#include "Section.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

Section::Section(QWidget *parent) : Section{nullptr, parent} {}

Section::Section(const char *title, QWidget *parent) : QWidget{parent}
{
  // Create layout
  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(8, 4, 8, 4);
  // Create label
  auto label = new QLabel{title, this};
  label->setContentsMargins(2, 2, 2, 0);
  // Create content
  content = new QWidget{this};

  // Add label if needed
  if (title)
    layout->addWidget(label);
  else
    label->hide();
  // Add content
  layout->addWidget(content);
}

QWidget *Section::getContent()
{
  return content;
}