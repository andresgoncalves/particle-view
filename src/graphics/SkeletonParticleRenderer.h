#ifndef SKELETON_PARTICLE_RENDERER_H
#define SKELETON_PARTICLE_RENDERER_H

#include <QtOpenGL/QOpenGLBuffer>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGL/QOpenGLVertexArrayObject>

#include "Renderer.h"
#include "../models/Particle.h"

class SkeletonParticleRenderer : public Renderer<Particle>
{
public:
  SkeletonParticleRenderer();

  void render(const Particle &particle, const RenderController &renderController) override;

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