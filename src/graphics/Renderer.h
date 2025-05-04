#ifndef RENDERER_H
#define RENDERER_H

#include "../controllers/AppContext.h"

template <typename T>
class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual void render(const T &element, const AppContext &appContext) = 0;
};

#endif