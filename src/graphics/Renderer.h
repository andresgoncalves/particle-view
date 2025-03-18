#ifndef RENDERER_H
#define RENDERER_H

#include "../controllers/ViewController.h"

template <typename T>
class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual void render(const T &element, const ViewController &viewController) = 0;
};

#endif