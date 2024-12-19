#ifndef PARTICLE_RENDERER_H
#define PARTICLE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "../models/Particle.h"

class ParticleRenderer
{
public:
  ParticleRenderer();

  void render(Particle &particle);

private:
  void loadShader();
  void loadBuffers();
  void loadVertices(std::vector<float> &vertices, size_t divisions = 24);
  void loadIndices(std::vector<uint> &indices, size_t divisions = 24);

  QOpenGLShaderProgram shaderProgram;
  QOpenGLVertexArrayObject vertexArray;
  QOpenGLBuffer vertexBuffer{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};
  uint indexCount;
};

#endif