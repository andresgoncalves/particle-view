#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui/QOpenGLFunctions>

#include <graphics/RenderContext.h>

/** Base renderer */
class Renderer : protected QOpenGLFunctions
{
protected:
  /** Init GL functions */
  Renderer() { initializeOpenGLFunctions(); }
};

#endif