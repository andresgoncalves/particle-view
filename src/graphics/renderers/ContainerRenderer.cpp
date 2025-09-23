#include "ContainerRenderer.h"

#include <graphics/shapes/CubeFactory.h>
#include <graphics/shapes/SphereFactory.h>
#include <graphics/shaders/GenericShader.h>

ContainerRenderer::ContainerRenderer(ContainerShape shape)
{
  switch (shape)
  {
  case ContainerShape::Cuboid:
  {
    auto factory = CubeFactory{};
    initBuffers(factory);
    break;
  }
  case ContainerShape::Ellipsoid:
  {
    auto factory = SphereFactory{24};
    initBuffers(factory);
    break;
  }
  }
}

void ContainerRenderer::render(const Container &container, RenderContext &renderContext)
{
  // Skip render if needed
  if (!container.enabled)
    return;

  // Get colors and matrix
  auto matrix = getMatrix(container, renderContext);

  // Start painting
  auto shader = GenericShader::getInstance();
  vertexArray.bind();
  shader->bind();

  // Set uniforms
  shader->setColor(container.color);
  shader->setMatrix(matrix);

  // Draw cube skeleton
  indexBuffers.skeleton.bind();
  glDrawElements(GL_LINES, indexBuffers.skeleton.size(), GL_UNSIGNED_INT, nullptr);

  // End painting
  vertexArray.release();
}

QMatrix4x4 ContainerRenderer::getMatrix(const Container &container, RenderContext &renderContext) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(container.center);
  modelMatrix.scale(container.size);

  auto modelViewProjectionMatrix = renderContext.appContext.viewController.getViewProjectionMatrix() * modelMatrix;

  return modelViewProjectionMatrix;
}

void ContainerRenderer::initBuffers(const BasicShapeFactory &factory)
{
  vertexArray.create();
  vertexArray.bind();

  auto vertices = factory.buildVertices();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto solidIndices = factory.buildIndices();

  indexBuffers.solid.create();
  indexBuffers.solid.bind();
  indexBuffers.solid.allocate(solidIndices.data(), solidIndices.size() * sizeof(solidIndices[0]));

  auto skeletonIndices = factory.buildOutlineIndices();

  indexBuffers.skeleton.create();
  indexBuffers.skeleton.bind();
  indexBuffers.skeleton.allocate(skeletonIndices.data(), skeletonIndices.size() * sizeof(skeletonIndices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}
