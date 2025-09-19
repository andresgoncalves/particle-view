#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui/QPainter>
#include <QtGui/QOpenGLFunctions>

#include <controllers/AppContext.h>

/** Interface template for rendering an object */
template <typename T>
class Renderer : protected QOpenGLFunctions
{
public:
  virtual ~Renderer() = default;

  /** Render an object */
  virtual void render(const T &element, const AppContext &appContext) = 0;
  /** Render an object with painter */
  virtual void render(const T &element, const AppContext &appContext, QPainter &painter, QSize viewportSize)
  {
    return render(element, appContext);
  }
};

template <>
class Renderer<void> : protected QOpenGLFunctions
{
public:
  virtual ~Renderer() = default;

  /** Render an object */
  virtual void render(const AppContext &appContext) = 0;
  /** Render an object with painter */
  virtual void render(const AppContext &appContext, QPainter &painter, QSize viewportSize)
  {
    return render(appContext);
  }
};

#endif