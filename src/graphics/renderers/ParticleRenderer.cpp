#include "ParticleRenderer.h"

#include <graphics/shapes/SphereFactory.h>
#include <graphics/shaders/GenericShader.h>

ParticleRenderer::ParticleRenderer()
{
  initBuffers();
}

void ParticleRenderer::render(const Particle &particle, RenderContext &renderContext)
{
  // Skip render if needed
  if (!shouldRender(particle, renderContext))
    return;

  // Get colors and matrix
  auto color = getColor(particle, renderContext);
  auto matrix = getMatrix(particle, renderContext);

  // Start painting
  auto shader = GenericShader::getInstance();
  vertexArray.bind();
  shader->bind();

  // Set uniforms
  shader->setColor(color);
  shader->setMatrix(matrix);

  switch (renderContext.appContext.viewController.particleShape)
  {
  // Draw solid sphere
  case ViewController::Solid:
    indexBuffers.solid.bind();
    glDrawElements(GL_TRIANGLES, indexBuffers.solid.size(), GL_UNSIGNED_INT, nullptr);
    // Draw black skeleton
    color = QColor{};
    shader->setColor(color);
  // Draw sphere skeleton
  case ViewController::Skeleton:
    indexBuffers.skeleton.bind();
    glDrawElements(GL_LINES, indexBuffers.skeleton.size(), GL_UNSIGNED_INT, nullptr);
    break;
  }

  // End painting
  vertexArray.release();
}

bool ParticleRenderer::shouldRender(const Particle &particle, RenderContext &renderContext) const
{
  auto displayRule = renderContext.appContext.displayController.getMatchingParticleRule(particle);
  if (!displayRule.isVisible())
    return false;

  switch (renderContext.appContext.viewController.projectionMode)
  {
  case ViewController::Perspective:
  {
    auto viewProjectionMatrix = renderContext.appContext.viewController.getViewProjectionMatrix();

    auto nearPlane = viewProjectionMatrix.row(3) + viewProjectionMatrix.row(2);
    nearPlane /= nearPlane.toVector3D().length();

    float distance = QVector3D::dotProduct(nearPlane.toVector3D(), particle.getPosition()) + nearPlane.w();

    return distance >= particle.getRadius();
  }
  default:
    return true;
  }
}

QColor ParticleRenderer::getColor(const Particle &particle, RenderContext &renderContext) const
{
  auto displayRule = renderContext.appContext.displayController.getMatchingParticleRule(particle);
  return displayRule.getColorStrategy()->getColor(particle);
}

QMatrix4x4 ParticleRenderer::getMatrix(const Particle &particle, RenderContext &renderContext) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(particle.getPosition());
  modelMatrix.scale(particle.getRadius());

  auto modelViewProjectionMatrix = renderContext.appContext.viewController.getViewProjectionMatrix() * modelMatrix;

  return modelViewProjectionMatrix;
}

void ParticleRenderer::initBuffers()
{
  auto sphereFactory = SphereFactory{24};

  vertexArray.create();
  vertexArray.bind();

  auto vertices = sphereFactory.buildVertices();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto solidIndices = sphereFactory.buildIndices();

  indexBuffers.solid.create();
  indexBuffers.solid.bind();
  indexBuffers.solid.allocate(solidIndices.data(), solidIndices.size() * sizeof(solidIndices[0]));

  auto skeletonIndices = sphereFactory.buildOutlineIndices();

  indexBuffers.skeleton.create();
  indexBuffers.skeleton.bind();
  indexBuffers.skeleton.allocate(skeletonIndices.data(), skeletonIndices.size() * sizeof(skeletonIndices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}
