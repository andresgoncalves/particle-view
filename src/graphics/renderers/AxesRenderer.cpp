#include "AxesRenderer.h"

#include <graphics/shaders/GenericShader.h>
#include <graphics/shapes/ArrowFactory.h>

AxesRenderer::AxesRenderer()
{
  initBuffers();
}

void AxesRenderer::render(RenderContext &renderContext)
{
  auto matrices = getMatrices(renderContext);

  // Start GL painting
  auto shader = GenericShader::getInstance();
  renderContext.painter.beginNativePainting();
  vertexArray.bind();
  shader->bind();

  // Paint axes
  for (int i = 0; i < 3; i++)
  {
    shader->setMatrix(matrices[i]);
    shader->setColor(axisColors[i]);
    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
  }

  // End GL painting
  vertexArray.release();
  renderContext.painter.endNativePainting();

  // Paint labels
  renderContext.painter.setRenderHint(QPainter::Antialiasing);
  renderContext.painter.setFont(QFont("Helvetica", 20));
  auto fontMetrics = QFontMetricsF{renderContext.painter.font()};
  for (int i = 0; i < 3; i++)
  {
    auto normalizedPoint = (matrices[i].map({0.0f, 1.25f, 0.0f}) + QVector3D{1.0f, 1.0f, 1.0f}) / 2.0f;
    auto textRect = fontMetrics.boundingRect(axisLabels[i]);
    textRect.adjust(-2, -2, 2, 2);
    textRect.moveCenter({normalizedPoint.x() * renderContext.viewportSize.width(),
                         (1.0f - normalizedPoint.y()) * renderContext.viewportSize.height()});
    renderContext.painter.setPen(axisColors[i]);
    renderContext.painter.drawText(textRect, Qt::AlignCenter, axisLabels[i]);
  }
}

void AxesRenderer::initBuffers()
{
  auto arrowFactory = ArrowFactory{24};

  vertexArray.create();
  vertexArray.bind();

  auto vertices = arrowFactory.buildVertices();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto indices = arrowFactory.buildIndices();

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(indices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}

std::array<QMatrix4x4, 3> AxesRenderer::getMatrices(RenderContext &renderContext) const
{
  // Axis size
  float axisSize = renderContext.appContext.viewController.axisSize;

  // Locate axes in viewport
  auto viewProjectionMatrix = renderContext.appContext.viewController.getProjectionMatrix(ViewController::Ortho);
  viewProjectionMatrix.translate((-renderContext.appContext.viewController.getViewport().toVector3D() + QVector3D{axisSize * 1.25f, axisSize * 1.25f, -1.0f}));
  viewProjectionMatrix.scale(axisSize);

  // Axis rotations
  std::array<QMatrix4x4, 3> modelMatrices;
  // Rotate to X axis
  modelMatrices[0].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}));
  // Rotate to Y axis
  modelMatrices[1].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));
  // Rotate to Z axis
  modelMatrices[2].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));

  // Model view projection matrices
  std::array<QMatrix4x4, 3> modelViewProjectionMatrices;
  for (int i = 0; i < 3; i++)
  {
    modelViewProjectionMatrices[i] = viewProjectionMatrix * renderContext.appContext.viewController.getRotationMatrix() * modelMatrices[i];
  }

  return modelViewProjectionMatrices;
}