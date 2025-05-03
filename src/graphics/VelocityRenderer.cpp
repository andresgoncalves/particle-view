#include "VelocityRenderer.h"

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

VelocityRenderer::VelocityRenderer()
{
  loadShader();
  loadBuffers();
}

void VelocityRenderer::render(const Particle &particle, const ViewController &viewController)
{
  float width = 0.25f;
  float height = 10.f * particle.velocity.length();

  // if (height < 0.1f)
  //   return;

  auto headModelMatrix = getHeadModelMatrix(particle.position, particle.velocity, 0.25f, 10.f * particle.velocity.length());
  auto bodyModelMatrix = getBodyModelMatrix(particle.position, particle.velocity, 0.25f, 10.f * particle.velocity.length());

  shaderProgram.bind();
  vertexArray.bind();

  auto type = particle.customProperties.find("type");
  if (type == particle.customProperties.end())
  {
    shaderProgram.setUniformValue("color", {0.0f, 0.0f, 1.0f});
  }
  else if (type->second == 1)
  {
    shaderProgram.setUniformValue("color", {1.0f, 0.0f, 0.0f});
  }
  else
  {
    shaderProgram.setUniformValue("color", {1.0f, 1.0f, 0.0f});
  }

  indexBuffers.arrowHead.bind();
  shaderProgram.setUniformValue("modelViewProjectionMatrix", viewController.getViewProjectionMatrix() * headModelMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.arrowHead.size(), GL_UNSIGNED_INT, nullptr);

  indexBuffers.arrowBody.bind();
  shaderProgram.setUniformValue("modelViewProjectionMatrix", viewController.getViewProjectionMatrix() * bodyModelMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.arrowBody.size(), GL_UNSIGNED_INT, nullptr);

  vertexArray.release();
  shaderProgram.release();
}

QMatrix4x4 VelocityRenderer::getBodyModelMatrix(QVector3D center, QVector3D direction, float width, float height) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.scale(width, height, width);

  return modelMatrix;
}

QMatrix4x4 VelocityRenderer::getHeadModelMatrix(QVector3D center, QVector3D direction, float width, float height) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.translate(0, height * arrowFactory.bodyHeight, 0);
  modelMatrix.scale(width);
  modelMatrix.translate(0, -arrowFactory.bodyHeight, 0);

  return modelMatrix;
}

void VelocityRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void VelocityRenderer::loadBuffers()
{
  vertexArray.create();
  vertexArray.bind();

  auto vertices = arrowFactory.buildVertices();

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto bodyIndices = arrowFactory.buildBodyIndices();

  indexBuffers.arrowBody.create();
  indexBuffers.arrowBody.bind();
  indexBuffers.arrowBody.allocate(bodyIndices.data(), bodyIndices.size() * sizeof(bodyIndices[0]));

  auto headIndices = arrowFactory.buildHeadIndices();

  indexBuffers.arrowHead.create();
  indexBuffers.arrowHead.bind();
  indexBuffers.arrowHead.allocate(headIndices.data(), headIndices.size() * sizeof(headIndices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}