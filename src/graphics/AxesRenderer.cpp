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
  // Axis colors
  QVector3D colors[] = {
      QVector3D{1.0f, 0.0f, 0.0f},
      QVector3D{0.0f, 1.0f, 0.0f},
      QVector3D{0.0f, 0.0f, 1.0f},
  };
  // Axis rotations
  QMatrix4x4 modelMatrices[] = {
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

  // Axis size
  float size = appContext.viewController.axisSize;

  // Locate axes in viewport
  auto viewProjectionMatrix = appContext.viewController.getProjectionMatrix(ViewController::Ortho);
  viewProjectionMatrix.translate((-appContext.viewController.getViewport().toVector3D() + QVector3D{size, size, -1.0f}));
  viewProjectionMatrix.scale(size);

  // Bind objects
  shaderProgram.bind();
  vertexArray.bind();

  // Draw each axis
  for (int i = 0; i < 3; i++)
  {
    auto modelViewProjectionMatrix = viewProjectionMatrix * appContext.viewController.getRotationMatrix() * modelMatrices[i];
    shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);
    shaderProgram.setUniformValue("color", colors[i]);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
  }

  // Release objects
  vertexArray.release();
  shaderProgram.release();
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