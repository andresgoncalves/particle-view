#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <graphics/RenderContext.h>
#include <graphics/shapes/BasicShapeFactory.h>
#include <models/Particle.h>

#include "Renderer.h"

/** Particle renderer */
class ParticleRenderer : protected Renderer
{
  struct Shape;

public:
  /** Create particle renderer */
  ParticleRenderer();

  /** Render particle */
  void render(const Particle &particle, RenderContext &renderContext);

private:
  /** Initialize buffers */
  void initBuffers(Shape &shape, BasicShapeFactory *shapeFactory);

  /** Check if particle should render  */
  bool shouldRender(const Particle &particle, RenderContext &renderContext) const;
  /** Get particle color */
  QColor getColor(const Particle &particle, RenderContext &renderContext) const;
  /** Get particle matrix */
  QMatrix4x4 getMatrix(const Particle &particle, RenderContext &renderContext) const;

  struct Shape
  {
    /** Shape vertex array object */
    QOpenGLVertexArrayObject vertexArray;
    /** Shape vertex buffer */
    QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
    /** Shape index buffers */
    struct IndexBuffers
    {
      QOpenGLBuffer solid{QOpenGLBuffer::IndexBuffer};
      QOpenGLBuffer skeleton{QOpenGLBuffer::IndexBuffer};
    } indexBuffers;
  } sphere, circle;
};

#endif