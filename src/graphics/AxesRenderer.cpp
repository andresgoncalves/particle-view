#include "AxesRenderer.h"

#include "shapes/ArrowFactory.h"

inline const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform vec3 color;\n"
    "uniform mat4 modelViewProjectionMatrix;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0f);\n"
    "    vertexColor = vec4(color, 1.0f);\n"
    "}\n";

inline const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec4 vertexColor;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "    fragmentColor = vertexColor;\n"
    "}\n";

AxesRenderer::AxesRenderer()
{
  loadShader();
  loadBuffers();
}

void AxesRenderer::render(const AppContext &appContext)
{
}

void AxesRenderer::render(const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
  // Axis size
  float axisSize = appContext.viewController.axisSize;

  // Locate axes in viewport
  auto viewProjectionMatrix = appContext.viewController.getProjectionMatrix(ViewController::Ortho);
  viewProjectionMatrix.translate((-appContext.viewController.getViewport().toVector3D() + QVector3D{axisSize * 1.25f, axisSize * 1.25f, -1.0f}));
  viewProjectionMatrix.scale(axisSize);

  // Axis rotations
  QMatrix4x4 modelMatrices[3] = {
      QMatrix4x4{},
      QMatrix4x4{},
      QMatrix4x4{},
  };
  // Rotate to X axis
  modelMatrices[0].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}));
  // Rotate to Y axis
  modelMatrices[1].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}));
  // Rotate to Z axis
  modelMatrices[2].rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));

  // Model view projection matrices
  QMatrix4x4 modelViewProjectionMatrices[3] = {
      QMatrix4x4{},
      QMatrix4x4{},
      QMatrix4x4{},
  };
  for (int i = 0; i < 3; i++)
  {
    modelViewProjectionMatrices[i] = viewProjectionMatrix * appContext.viewController.getRotationMatrix() * modelMatrices[i];
  }

  // Paint axes
  paintAxes(modelViewProjectionMatrices, appContext, painter, viewportSize);
  // Paint labels
  paintLabels(modelViewProjectionMatrices, appContext, painter, viewportSize);
}

void AxesRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void AxesRenderer::loadBuffers()
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

  indexCount = indices.size();

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}

void AxesRenderer::paintAxes(QMatrix4x4 modelViewProjectionMatrices[3], const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
  // Bind objects
  painter.beginNativePainting();
  shaderProgram.bind();
  vertexArray.bind();

  // Draw each axis
  for (int i = 0; i < 3; i++)
  {
    shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrices[i]);
    shaderProgram.setUniformValue("color", QVector3D{
                                               axisColors[i].redF(),
                                               axisColors[i].greenF(),
                                               axisColors[i].blueF()});
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
  }

  // Release objects
  vertexArray.release();
  shaderProgram.release();
  painter.endNativePainting();
}

void AxesRenderer::paintLabels(QMatrix4x4 modelViewProjectionMatrices[3], const AppContext &appContext, QPainter &painter, QSize viewportSize)
{
  // Paint each label
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setFont(QFont("Helvetica", 20));
  auto fontMetrics = QFontMetricsF{painter.font()};
  for (int i = 0; i < 3; i++)
  {
    auto normalizedPoint = (modelViewProjectionMatrices[i] * QVector3D{0.0f, 1.25f, 0.0f} + QVector3D{1.0f, 1.0f, 1.0f}) / 2.0f;
    auto textRect = fontMetrics.boundingRect(axisLabels[i]);
    textRect.adjust(-2, -2, 2, 2);
    textRect.moveCenter({normalizedPoint.x() * viewportSize.width(),
                         (1.0f - normalizedPoint.y()) * viewportSize.height()});
    painter.setPen(axisColors[i]);
    painter.drawText(textRect, Qt::AlignCenter, axisLabels[i]);
  }
}