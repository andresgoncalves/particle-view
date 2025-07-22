#include "ColorScaleRenderer.h"

#include <QtGui/QLinearGradient>

ColorScaleRenderer::ColorScaleRenderer()
{
}

void ColorScaleRenderer::render(const GradientColorStrategy &gradientColorStrategy, const AppContext &appContext)
{
}

void ColorScaleRenderer::render(const GradientColorStrategy &gradientColorStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
  // Get size
  auto colorScaleSize = QSizeF{
      32.0, viewportSize.height() * 0.75};

  // Get gradient brush
  auto gradient = QLinearGradient{0, 0, 0, 1};
  gradient.setCoordinateMode(QLinearGradient::ObjectBoundingMode);
  gradient.setColorAt(0, gradientColorStrategy.getEnd().second);
  gradient.setColorAt(1, gradientColorStrategy.getStart().second);

  // Calculate rect
  auto colorScaleRect = QRectF{
      viewportSize.width() - 2 * colorScaleSize.width(),
      (viewportSize.height() - colorScaleSize.height()) / 2,
      colorScaleSize.width(),
      colorScaleSize.height()};

  // Paint rect
  painter.fillRect(colorScaleRect, gradient);
  painter.setPen(Qt::white);
  painter.drawRect(colorScaleRect);

  // Paint text
  painter.fillRect(colorScaleRect, gradient);
  painter.setPen(Qt::white);
  painter.drawRect(colorScaleRect);

  // Setup text painter
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setFont(QFont("Helvetica", 16));
  auto fontMetrics = QFontMetricsF{painter.font()};

  // Paint start label
  auto startText = QString::number(gradientColorStrategy.getStart().first, 'f', 3);
  auto startTextRect = fontMetrics.boundingRect(startText);
  startTextRect.adjust(-2, -2, 2, 2);
  startTextRect.moveTo(
      colorScaleRect.left() - startTextRect.width() - 8,
      colorScaleRect.bottom() - startTextRect.height() / 2);
  painter.drawText(startTextRect, Qt::AlignRight, startText);

  // Paint end label
  auto endText = QString::number(gradientColorStrategy.getEnd().first, 'f', 3);
  auto endTextRect = fontMetrics.boundingRect(endText);
  endTextRect.adjust(-2, -2, 2, 2);
  endTextRect.moveTo(
      colorScaleRect.left() - endTextRect.width() - 8,
      colorScaleRect.top() - endTextRect.height() / 2);
  painter.drawText(endTextRect, Qt::AlignRight, endText);
}
