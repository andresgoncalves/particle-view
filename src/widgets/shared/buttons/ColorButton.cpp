#include "ColorButton.h"

#include <QtGui/QPainter>
#include <QtGui/QLinearGradient>

#include <utils/color/SolidColorStrategy.h>
#include <utils/color/ColorScaleStrategy.h>

ColorButton::ColorButton(QWidget *parent) : QPushButton{nullptr, parent}
{
  setFixedSize(48, 16);
}

void ColorButton::setSolidColor(QColor color)
{
  brush = color;
}

void ColorButton::setColorScale(QColor start, QColor end)
{
  auto gradient = QLinearGradient{0, 0, 1, 0};
  gradient.setCoordinateMode(QLinearGradient::ObjectBoundingMode);
  gradient.setColorAt(0, start);
  gradient.setColorAt(1, end);
  brush = gradient;
}

void ColorButton::setColorStrategy(ColorStrategy *colorStrategy)
{
  if (auto solidColorStrategy = dynamic_cast<SolidColorStrategy *>(colorStrategy))
    setSolidColor(solidColorStrategy->getSolidColor());
  else if (auto gradientColorStrategy = dynamic_cast<ColorScaleStrategy *>(colorStrategy))
    setColorScale(gradientColorStrategy->getStart().second, gradientColorStrategy->getEnd().second);
}

void ColorButton::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setBrush(brush);
  painter.drawRect(rect());
}