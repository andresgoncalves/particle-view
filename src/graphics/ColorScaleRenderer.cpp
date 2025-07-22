#include "ColorScaleRenderer.h"

#include <QtGui/QLinearGradient>

ColorScaleRenderer::ColorScaleRenderer()
{
}

void ColorScaleRenderer::render(const ColorScaleStrategy &colorScaleStrategy, const AppContext &appContext)
{
}

void ColorScaleRenderer::render(const ColorScaleStrategy &colorScaleStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
    // Get size
    auto colorScaleSize = QSizeF{
        32.0, viewportSize.height() * 0.75};

    // Calculate rect
    auto colorScaleRect = QRectF{
        viewportSize.width() - 2 * colorScaleSize.width(),
        (viewportSize.height() - colorScaleSize.height()) / 2,
        colorScaleSize.width(),
        colorScaleSize.height()};

    // Paint color scale
    paintColorScale(colorScaleRect, colorScaleStrategy, appContext, painter, viewportSize);
    // Paint labels
    paintLabels(colorScaleRect, colorScaleStrategy, appContext, painter, viewportSize);
}

void ColorScaleRenderer::paintColorScale(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
    // Get gradient brush
    auto gradient = QLinearGradient{0, 0, 0, 1};
    gradient.setCoordinateMode(QLinearGradient::ObjectBoundingMode);
    gradient.setColorAt(0, colorScaleStrategy.getEnd().second);
    gradient.setColorAt(1, colorScaleStrategy.getStart().second);

    // Paint rect
    painter.fillRect(colorScaleRect, gradient);
    painter.setPen(Qt::white);
    painter.drawRect(colorScaleRect);

    // Paint text
    painter.fillRect(colorScaleRect, gradient);
    painter.setPen(Qt::white);
    painter.drawRect(colorScaleRect);
}

void ColorScaleRenderer::paintLabels(QRectF colorScaleRect, const ColorScaleStrategy &colorScaleStrategy, const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
    // Setup text painter
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(QFont("Helvetica", 16));
    auto fontMetrics = QFontMetricsF{painter.font()};

    // Paint start label
    auto startText = QString::number(colorScaleStrategy.getStart().first, 'f', 3);
    auto startTextRect = fontMetrics.boundingRect(startText);
    startTextRect.adjust(-2, -2, 2, 2);
    startTextRect.moveTo(
        colorScaleRect.left() - startTextRect.width() - 8,
        colorScaleRect.bottom() - startTextRect.height() / 2);
    painter.drawText(startTextRect, Qt::AlignRight, startText);

    // Paint end label
    auto endText = QString::number(colorScaleStrategy.getEnd().first, 'f', 3);
    auto endTextRect = fontMetrics.boundingRect(endText);
    endTextRect.adjust(-2, -2, 2, 2);
    endTextRect.moveTo(
        colorScaleRect.left() - endTextRect.width() - 8,
        colorScaleRect.top() - endTextRect.height() / 2);
    painter.drawText(endTextRect, Qt::AlignRight, endText);
}