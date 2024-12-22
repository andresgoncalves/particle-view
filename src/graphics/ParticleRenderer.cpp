#include "ParticleRenderer.h"

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

ParticleRenderer::ParticleRenderer()
{
  loadShader();
  loadBuffers();
}

const bool skeletonMode = false;

void ParticleRenderer::render(const Particle &particle, const RenderController &renderController)
{
  if (!shouldRender(particle, renderController))
    return;

  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(particle.position);
  modelMatrix.scale(particle.radius);

  auto modelViewProjectionMatrix = renderController.getViewProjectionMatrix() * modelMatrix;

  shaderProgram.bind();
  vertexArray.bind();

  shaderProgram.setUniformValue("color", particle.color);
  shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);

  drawElements(renderController.particleShape);

  vertexArray.release();
  shaderProgram.release();
}

bool ParticleRenderer::shouldRender(const Particle &particle, const RenderController &renderController)
{

  switch (renderController.projectionMode)
  {
  case RenderController::Perspective:
  {
    auto viewProjectionMatrix = renderController.getViewProjectionMatrix();

    auto nearPlane = viewProjectionMatrix.row(3) + viewProjectionMatrix.row(2);
    nearPlane /= nearPlane.toVector3D().length();

    float distance = QVector3D::dotProduct(nearPlane.toVector3D(), particle.position) + nearPlane.w();

    return distance >= particle.radius;
  }
  default:
    return true;
  }
}

void ParticleRenderer::drawElements(RenderController::ParticleShape mode)
{
  switch (mode)
  {
  case RenderController::Solid:
    indexBuffers.solid.bind();
    glDrawElements(GL_TRIANGLES, indexBuffers.solid.size(), GL_UNSIGNED_INT, nullptr);
    break;
  case RenderController::Skeleton:
    indexBuffers.skeleton.bind();
    glDrawElements(GL_LINES, indexBuffers.skeleton.size(), GL_UNSIGNED_INT, nullptr);
    break;
  }
}

void ParticleRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void ParticleRenderer::loadBuffers()
{
  vertexArray.create();
  vertexArray.bind();

  auto vertices = std::vector<float>{};
  loadVertices(vertices);

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto solidIndices = std::vector<uint>{};
  loadSolidIndices(solidIndices);

  indexBuffers.solid.create();
  indexBuffers.solid.bind();
  indexBuffers.solid.allocate(solidIndices.data(), solidIndices.size() * sizeof(solidIndices[0]));

  auto skeletonIndices = std::vector<uint>{};
  loadSkeletonIndices(skeletonIndices);

  indexBuffers.skeleton.create();
  indexBuffers.skeleton.bind();
  indexBuffers.skeleton.allocate(skeletonIndices.data(), skeletonIndices.size() * sizeof(skeletonIndices[0]));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}

void ParticleRenderer::loadVertices(std::vector<float> &vertices, size_t divisions)
{
  for (int latitude = 0; latitude <= divisions; latitude++)
  {
    float theta = latitude * M_PI / divisions;
    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);

    for (int longitude = 0; longitude <= divisions; longitude++)
    {
      float phi = 2 * longitude * M_PI / divisions;
      float sinPhi = std::sin(phi);
      float cosPhi = std::cos(phi);

      float x = cosPhi * sinTheta;
      float y = cosTheta;
      float z = sinPhi * sinTheta;

      vertices.push_back(x);
      vertices.push_back(y);
      vertices.push_back(z);
    }
  }
}

void ParticleRenderer::loadSolidIndices(std::vector<uint> &indices, size_t divisions)
{
  for (int latitude = 0; latitude < divisions; latitude++)
  {
    for (int longitude = 0; longitude < divisions; longitude++)
    {
      int first = (latitude * (divisions + 1)) + longitude;
      int second = first + divisions + 1;

      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      indices.push_back(second);
      indices.push_back(second + 1);
      indices.push_back(first + 1);
    }
  }
}

void ParticleRenderer::loadSkeletonIndices(std::vector<uint> &indices, size_t divisions)
{
  for (int latitude = 0; latitude < divisions; latitude++)
  {
    for (int longitude = 0; longitude < divisions; longitude++)
    {
      int first = (latitude * (divisions + 1)) + longitude;
      int second = first + divisions + 1;

      indices.push_back(first);
      indices.push_back(first + 1);

      indices.push_back(first);
      indices.push_back(second);
    }
  }
}