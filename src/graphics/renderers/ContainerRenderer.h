#ifndef CONTAINER_RENDERER_H
#define CONTAINER_RENDERER_H

#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <graphics/RenderContext.h>
#include <graphics/shapes/BasicShapeFactory.h>
#include <models/Container.h>

#include "Renderer.h"

/** Container renderer */
class ContainerRenderer : protected Renderer
{
public:
  /** Create container renderer */
  ContainerRenderer(ContainerShape shape);

  /** Render container */
  void render(const Container &container, RenderContext &renderContext);

private:
  /** Initialize buffers */
  void initBuffers(const BasicShapeFactory &factory);

  /** Get container matrix */
  QMatrix4x4 getMatrix(const Container &container, RenderContext &renderContext) const;

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
};

#endif