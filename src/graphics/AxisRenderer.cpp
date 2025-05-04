#include "AxisRenderer.h"

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

AxisRenderer::AxisRenderer()
{
  loadShader();
  loadBuffers();
}

void AxisRenderer::render(const Axis &axis, const AppContext &appContext)
{
  auto modelMatrix = QMatrix4x4{};
  auto color = QVector3D{};

  switch (axis)
  {
  case Axis::X:
    modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}));
    color = {1.0f, 0.0f, 0.0f};
    break;
  case Axis::Y:
    color = {0.0f, 1.0f, 0.0f};
    break;
  case Axis::Z:
    modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}));
    color = {0.0f, 0.0f, 1.0f};
    break;
  }

  float size = appContext.viewController.axisSize;

  auto viewProjectionMatrix = appContext.viewController.getProjectionMatrix(ViewController::Ortho);
  viewProjectionMatrix.translate((-appContext.viewController.getViewport().toVector3D() + QVector3D{size, size, -1.0f}));
  viewProjectionMatrix.scale(size);

  auto modelViewProjectionMatrix = viewProjectionMatrix * appContext.viewController.getRotationMatrix() * modelMatrix;

  shaderProgram.bind();
  vertexArray.bind();

  shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);
  shaderProgram.setUniformValue("color", color);
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

  vertexArray.release();
  shaderProgram.release();
}

void AxisRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void AxisRenderer::loadBuffers()
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