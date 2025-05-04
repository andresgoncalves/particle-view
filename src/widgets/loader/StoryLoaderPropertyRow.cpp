#include "StoryLoaderPropertyRow.h"

#include <map>

#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

StoryLoaderPropertyRow::StoryLoaderPropertyRow(const char *title, bool canDelete, QWidget *parent) : QWidget{parent}
{
  auto label = new QLabel{title, this};
  widget = new QWidget{this};

  layout = new QGridLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(label, 0, 0);
  layout->addWidget(widget, 0, 1);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 0);
  layout->setColumnMinimumWidth(2, 64);
  layout->setHorizontalSpacing(8);

  if (canDelete)
  {
    deleteButton = new QPushButton{"X", this};
    layout->addWidget(deleteButton, 0, 2);
  }
  else
  {
    layout->addWidget(new QWidget{this}, 0, 2);
  }
}

QPushButton *StoryLoaderPropertyRow::getDeleteButton() const
{
  return deleteButton;
};

void StoryLoaderPropertyRow::setWidget(QWidget *widget)
{
  layout->replaceWidget(this->widget, widget);
  this->widget->deleteLater();
  this->widget = widget;
}