#ifndef VECTOR_RENDERER_H
#define VECTOR_RENDERER_H

#include <QtCore/QSize>
#include <QtGui/QColor>
#include <QtGui/QMatrix4x4>

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include <graphics/shapes/ArrowFactory.h>
#include <graphics/RenderContext.h>
#include <models/Particle.h>

#include "Renderer.h"

/** Vector property renderer */
class VectorRenderer : protected Renderer
{
public:
  /** Create vector property renderer */
  VectorRenderer();

  /** Render vector property */
  void render(const Particle &particle, std::string property, RenderContext &renderContext);

private:
  /** Initialize buffers */
  void initBuffers();

  /** Get vector size */
  QSizeF getSize(QVector3D vector, std::string property, RenderContext &renderContext) const;
  /** Get vector body matrix */
  QMatrix4x4 getBodyModelMatrix(QVector3D center, QVector3D direction, QSizeF size) const;
  /** Get vector head matrix */
  QMatrix4x4 getHeadModelMatrix(QVector3D center, QVector3D direction, QSizeF size) const;
  /** Get vector color */
  QColor getColor(const Particle &particle, std::string property, RenderContext &renderContext) const;

  /** Shape vertex array object */
  QOpenGLVertexArrayObject vertexArray;
  /** Shape vertex buffer */
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  /** Shape index buffers */
  struct IndexBuffers
  {
    QOpenGLBuffer head{QOpenGLBuffer::IndexBuffer};
    QOpenGLBuffer body{QOpenGLBuffer::IndexBuffer};
  } indexBuffers;

  /** Arrow factory */
  ArrowFactory arrowFactory{24};
};

#endif