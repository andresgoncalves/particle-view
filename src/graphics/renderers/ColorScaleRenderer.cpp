#include "ColorScaleRenderer.h"

#include <QtGui/QLinearGradient>

ColorScaleRenderer::ColorScaleRenderer()
{
}

void ColorScaleRenderer::render(const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext)
{
  // Get rectangle
  auto colorScaleRect = getRect(renderContext.viewportSize);

  // Paint color scale
  paintColorScale(colorScaleRect, colorScaleStrategy, renderContext);
  // Paint labels
  paintLabels(colorScaleRect, colorScaleStrategy, renderContext);
}

std::optional<float> ColorScaleRenderer::getValueAt(QPointF point, const ColorScaleStrategy &colorScaleStrategy, QSize viewportSize) const
{
  // Get rectangle
  auto colorScaleRect = getRect(viewportSize);

  if (!colorScaleRect.contains(point))
    return std::nullopt;

  auto normalizedValue = 1.0f - (point.y() - colorScaleRect.y()) / colorScaleRect.height();
  auto value = colorScaleStrategy.getStart().first + normalizedValue * (colorScaleStrategy.getEnd().first - colorScaleStrategy.getStart().first);

  return value;
}

QRectF ColorScaleRenderer::getRect(QSize viewportSize) const
{
  // Get size
  auto colorScaleSize = QSizeF{32.0, viewportSize.height() * 0.75};

  // Calculate rect
  auto colorScaleRect = QRectF{
      viewportSize.width() - 2 * colorScaleSize.width(),
      (viewportSize.height() - colorScaleSize.height()) / 2,
      colorScaleSize.width(),
      colorScaleSize.height()};

  return colorScaleRect;
}

void ColorScaleRenderer::paintColorScale(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext)
{
  // Get gradient brush
  auto gradient = QLinearGradient{0, 0, 0, 1};
  gradient.setCoordinateMode(QLinearGradient::ObjectBoundingMode);
  gradient.setColorAt(0, colorScaleStrategy.getEnd().second);
  gradient.setColorAt(1, colorScaleStrategy.getStart().second);

  // Paint rect
  renderContext.painter.fillRect(colorScaleRect, gradient);
  renderContext.painter.setPen(Qt::white);
  renderContext.painter.drawRect(colorScaleRect);

  // Paint text
  renderContext.painter.fillRect(colorScaleRect, gradient);
  renderContext.painter.setPen(Qt::white);
  renderContext.painter.drawRect(colorScaleRect);
}

void ColorScaleRenderer::paintLabels(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, RenderContext &renderContext)
{
  // Setup text painter
  renderContext.painter.setRenderHint(QPainter::Antialiasing);
  renderContext.painter.setFont(QFont("Helvetica", 16));
  auto fontMetrics = QFontMetricsF{renderContext.painter.font()};

  // Paint start label
  auto startText = QString::number(colorScaleStrategy.getStart().first, 'f', 3);
  auto startTextRect = fontMetrics.boundingRect(startText);
  startTextRect.adjust(-2, -2, 2, 2);
  startTextRect.moveTo(
      colorScaleRect.left() - startTextRect.width() - 8,
      colorScaleRect.bottom() - startTextRect.height() / 2);
  renderContext.painter.drawText(startTextRect, Qt::AlignRight, startText);

  // Paint end label
  auto endText = QString::number(colorScaleStrategy.getEnd().first, 'f', 3);
  auto endTextRect = fontMetrics.boundingRect(endText);
  endTextRect.adjust(-2, -2, 2, 2);
  endTextRect.moveTo(
      colorScaleRect.left() - endTextRect.width() - 8,
      colorScaleRect.top() - endTextRect.height() / 2);
  renderContext.painter.drawText(endTextRect, Qt::AlignRight, endText);
}