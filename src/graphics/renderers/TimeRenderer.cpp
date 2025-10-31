#include "TimeRenderer.h"

TimeRenderer::TimeRenderer()
{
}

void TimeRenderer::render(float time, RenderContext &renderContext)
{
  // Setup text painter
  renderContext.painter.setRenderHint(QPainter::Antialiasing);
  renderContext.painter.setFont(QFont("Helvetica", 20));
  renderContext.painter.setPen({255, 255, 255});
  auto fontMetrics = QFontMetricsF{renderContext.painter.font()};

  // Paint start label
  auto timeText = QString::number(time, 'f', 3);
  auto timeTextRect = fontMetrics.boundingRect(timeText);
  timeTextRect.adjust(-2, -2, 2, 2);
  timeTextRect.moveTo(20, 20);
  renderContext.painter.drawText(timeTextRect, Qt::AlignLeft, timeText);
}
