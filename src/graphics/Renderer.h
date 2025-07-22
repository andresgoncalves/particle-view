#ifndef RENDERER_H
#define RENDERER_H

#include <controllers/AppContext.h>

/** Interface template for rendering an object */
template <typename T>
class Renderer
{
public:
  virtual ~Renderer() = default;

  /** Render an object */
  virtual void render(const T &element, const AppContext &appContext) = 0;
};

template <>
class Renderer<void>
{
public:
  virtual ~Renderer() = default;

  /** Render an object */
  virtual void render(const AppContext &appContext) = 0;
};

#endif