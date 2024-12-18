#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "AppWidget.h"
#include "GraphicsWidget.h"

AppWidget::AppWidget(QWidget *parent) : QWidget{parent}
{
  auto layout = new QVBoxLayout{this};
  layout->setContentsMargins(0, 0, 0, 0);

  auto font = this->font();
  font.setPointSize(24);

  auto label = new QLabel{"Hello, from particle-view!"};
  label->setFont(font);
  label->setContentsMargins(24, 16, 24, 16);
  auto graphicsWidget = new GraphicsWidget{};
  graphicsWidget->setMinimumSize(800, 600);

  layout->addWidget(label);
  layout->setAlignment(label, Qt::AlignCenter);
  layout->addWidget(graphicsWidget);
  layout->setAlignment(graphicsWidget, Qt::AlignCenter);

  setLayout(layout);
  adjustSize();
}