#include "VectorRenderer.h"

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

VectorRenderer::VectorRenderer()
{
  loadShader();
  loadBuffers();
}

void VectorRenderer::render(const std::pair<Particle, std::string> &input, const AppContext &appContext)
{
  auto [particle, property] = input;

  auto vectorIt = particle.vectorProperties.find(property);
  if (vectorIt == particle.vectorProperties.end())
    return;

  auto vector = vectorIt->second;

  auto metadata = appContext.animationController.getStory().metadata;
  auto largestVectorIt = metadata.largestVectors.find(property);
  auto largestVector = largestVectorIt == metadata.largestVectors.end() && largestVectorIt->second > 0 ? largestVectorIt->second : 1.0f;

  float width = 0.25f;
  float height = 5.0f * metadata.largestRadius * vector.length() / largestVector;

  auto headModelMatrix = getHeadModelMatrix(particle.position, vector, width, height);
  auto bodyModelMatrix = getBodyModelMatrix(particle.position, vector, width, height);

  shaderProgram.bind();
  vertexArray.bind();

  auto color = appContext.displayController.getDefaultColor();
  for (auto displayRule : appContext.displayController.getDisplayRules())
  {
    if (displayRule->isEnabled() && displayRule->test(particle))
      color = displayRule->getColor();
  }
  shaderProgram.setUniformValue("color", QVector3D{color.redF(), color.greenF(), color.blueF()});

  indexBuffers.arrowHead.bind();
  shaderProgram.setUniformValue("modelViewProjectionMatrix", appContext.viewController.getViewProjectionMatrix() * headModelMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.arrowHead.size(), GL_UNSIGNED_INT, nullptr);

  indexBuffers.arrowBody.bind();
  shaderProgram.setUniformValue("modelViewProjectionMatrix", appContext.viewController.getViewProjectionMatrix() * bodyModelMatrix);
  glDrawElements(GL_TRIANGLES, indexBuffers.arrowBody.size(), GL_UNSIGNED_INT, nullptr);

  vertexArray.release();
  shaderProgram.release();
}

QMatrix4x4 VectorRenderer::getBodyModelMatrix(QVector3D center, QVector3D direction, float width, float height) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.scale(width, height, width);

  return modelMatrix;
}

QMatrix4x4 VectorRenderer::getHeadModelMatrix(QVector3D center, QVector3D direction, float width, float height) const
{
  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(center);
  modelMatrix.rotate(QQuaternion::rotationTo({0.0f, 1.0f, 0.0f}, direction));
  modelMatrix.translate(0, height * arrowFactory.bodyHeight, 0);
  modelMatrix.scale(width);
  modelMatrix.translate(0, -arrowFactory.bodyHeight, 0);

  return modelMatrix;
}

void VectorRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void VectorRenderer::loadBuffers()
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