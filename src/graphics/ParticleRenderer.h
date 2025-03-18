#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"
#include "../models/Particle.h"

class ParticleRenderer : public Renderer<Particle>
{
public:
  ParticleRenderer();

  void render(const Particle &particle, const ViewController &viewController) override;

private:
  void loadShader();
  void loadBuffers();
  void loadVertices(std::vector<float> &vertices, size_t divisions = 24);
  void loadSolidIndices(std::vector<uint> &indices, size_t divisions = 24);
  void loadSkeletonIndices(std::vector<uint> &indices, size_t divisions = 24);

  bool shouldRender(const Particle &particle, const ViewController &viewController);
  void drawElements(ViewController::ParticleShape mode);

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};

  struct IndexBuffers
  {
    QOpenGLBuffer solid{QOpenGLBuffer::IndexBuffer};
    QOpenGLBuffer skeleton{QOpenGLBuffer::IndexBuffer};
  } indexBuffers;
};

#endif