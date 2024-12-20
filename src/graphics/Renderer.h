#ifndef RENDERER_H
#define RENDERER_H

#include "../controllers/RenderController.h"

template <typename T>
class Renderer
{
public:
  virtual void render(const T &element, const RenderController &renderController) = 0;
};

#endif