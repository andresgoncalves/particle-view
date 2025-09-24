#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <QtCore/QSize>
#include <QtGui/QPainter>

#include <controllers/AppContext.h>

struct RenderContext
{
  RenderContext(QSize viewportSize,
                QPainter &painter,
                AppContext &appContext) : viewportSize{viewportSize},
                                          painter{painter},
                                          appContext{appContext}
  {
  }

  const QSize viewportSize;
  QPainter &painter;
  AppContext &appContext;
};

#endif