#ifndef TIME_RENDERER_H
#define TIME_RENDERER_H

#include <optional>

#include <graphics/RenderContext.h>

#include "Renderer.h"

/** Color scale renderer */
class TimeRenderer : protected Renderer
{
public:
  /** Create simulation time renderer */
  TimeRenderer();

  /** Render simulation time */
  void render(float time, RenderContext &renderContext);
};

#endif