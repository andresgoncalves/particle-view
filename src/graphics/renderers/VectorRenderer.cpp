#include "VectorRenderer.h"

#include <graphics/shaders/GenericShader.h>
#include <graphics/shapes/ArrowFactory.h>

VectorRenderer::VectorRenderer()
{
  initBuffers();
}

void VectorRenderer::render(const Particle &particle, std::string property, RenderContext &renderContext)
{
  // Get vector
  auto vectorIt = particle.properties.find(property);
  if (vectorIt == particle.properties.end() || vectorIt->second.getType() != PropertyType::Vector)
    return;
  // Check display rule
  auto displayRule = renderContext.appContext.displayController.getMatchingVectorRule(particle, property);
  if (!displayRule.isVisible())
    return;

  auto vector = vectorIt->second.getValue<PropertyType::Vector>()->value;

  // Get colors and matrix
  auto size = getSize(vector, property, renderContext);
  auto color = getColor(particle, property, renderContext);
  auto bodyMatrix = renderContext.appContext.viewController.getViewProjectionMatrix() * getBodyModelMatrix(particle.getPosition(), vector, size);
  auto headMatrix = renderContext.appContext.viewController.getViewProjectionMatrix() * getHeadModelMatrix(particle.getPosition(), vector, size);

  // Start painting
  auto shader = GenericShader::getInstance();
  vertexArray.bind();
  shader->bind();

  // Set uniforms
  shader->setColor(color);

  // Paint arrow head
  indexBuffers.head.bind();
  shader->setMatrix(headMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.head.size(), GL_UNSIGNED_INT, nullptr);

  // Paint arrow body
  indexBuffers.body.bind();
  shader->setMatrix(bodyMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.body.size(), GL_UNSIGNED_INT, nullptr);

  // End painting
  vertexArray.release();
}

QMatrix4x4 VectorRenderer::getBodyModelMatrix(QVector3D center, QVector3D direction, QSizeF size) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.scale(size.width(), size.height(), size.width());

  return modelMatrix;
}

QMatrix4x4 VectorRenderer::getHeadModelMatrix(QVector3D center, QVector3D direction, QSizeF size) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.translate(0, size.height() * arrowFactory.bodyHeight, 0);
  modelMatrix.scale(size.width());
  modelMatrix.translate(0, -arrowFactory.bodyHeight, 0);

  return modelMatrix;
}

QSizeF VectorRenderer::getSize(QVector3D vector, std::string property, RenderContext &renderContext) const
{
  auto metadata = renderContext.appContext.animationController.getStory().metadata;
  auto maxValueIt = metadata.maxValues.find(property);
  auto maxValue = maxValueIt == metadata.maxValues.end() && maxValueIt->second > 0 ? maxValueIt->second : 1.0f;

  auto width = 0.25f;
  auto height = 5.0f * metadata.maxValues[Particle::RADIUS_PROPERTY] * vector.length() / maxValue;

  return {width, height};
}

QColor VectorRenderer::getColor(const Particle &particle, std::string property, RenderContext &renderContext) const
{
  auto displayRule = renderContext.appContext.displayController.getMatchingVectorRule(particle, property);
  return displayRule.getColorStrategy()->getColor(particle);
}

void VectorRenderer::initBuffers()
{
  vertexArray.create();
  vertexArray.bind();

  auto vertices = arrowFactory.buildVertices();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto bodyIndices = arrowFactory.buildBodyIndices();

  indexBuffers.body.create();
  indexBuffers.body.bind();
  indexBuffers.body.allocate(bodyIndices.data(), bodyIndices.size() * sizeof(bodyIndices[0]));

  auto headIndices = arrowFactory.buildHeadIndices();

  indexBuffers.head.create();
  indexBuffers.head.bind();
  indexBuffers.head.allocate(headIndices.data(), headIndices.size() * sizeof(headIndices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}