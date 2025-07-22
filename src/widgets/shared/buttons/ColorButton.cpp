#include "ColorButton.h"

#include <QtGui/QPainter>
#include <QtGui/QLinearGradient>

#include <utils/color/SolidColorStrategy.h>
#include <utils/color/GradientColorStrategy.h>

ColorButton::ColorButton(QWidget *parent) : QPushButton{nullptr, parent}
{
  setFixedSize(48, 16);
}

void ColorButton::setSolidColor(QColor color)
{
  brush = color;
}

void ColorButton::setGradientColor(QColor start, QColor end)
{
  auto gradient = QLinearGradient{0, 0, (double)width(), 0};
  gradient.setColorAt(0, start);
  gradient.setColorAt(1, end);
  brush = gradient;
}

void ColorButton::setColorStrategy(ColorStrategy *colorStrategy)
{
  if (auto solidColorStrategy = dynamic_cast<SolidColorStrategy *>(colorStrategy))
    setSolidColor(solidColorStrategy->getSolidColor());
  else if (auto gradientColorStrategy = dynamic_cast<GradientColorStrategy *>(colorStrategy))
    setGradientColor(gradientColorStrategy->getStart().second, gradientColorStrategy->getEnd().second);
}

void ColorButton::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setBrush(brush);
  painter.drawRect(rect());
}