#include "ParticleRenderer.h"

#include "shapes/SphereFactory.h"

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

void ParticleRenderer::render(const Particle &particle, const AppContext &appContext)
{
  if (!shouldRender(particle, appContext))
    return;

  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(particle.position);
  modelMatrix.scale(particle.radius);

  auto modelViewProjectionMatrix = appContext.viewController.getViewProjectionMatrix() * modelMatrix;

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

  shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);

  drawElements(appContext.viewController.particleShape);

  vertexArray.release();
  shaderProgram.release();
}

bool ParticleRenderer::shouldRender(const Particle &particle, const AppContext &appContext)
{
  switch (appContext.viewController.projectionMode)
  {
  case ViewController::Perspective:
  {
    auto viewProjectionMatrix = appContext.viewController.getViewProjectionMatrix();

    auto nearPlane = viewProjectionMatrix.row(3) + viewProjectionMatrix.row(2);
    nearPlane /= nearPlane.toVector3D().length();

    float distance = QVector3D::dotProduct(nearPlane.toVector3D(), particle.position) + nearPlane.w();

    return distance >= particle.radius;
  }
  default:
    return true;
  }
}

void ParticleRenderer::drawElements(ViewController::ParticleShape mode)
{
  switch (mode)
  {
  case ViewController::Solid:
    indexBuffers.solid.bind();
    glDrawElements(GL_TRIANGLES, indexBuffers.solid.size(), GL_UNSIGNED_INT, nullptr);
    shaderProgram.setUniformValue("color", {0.0f, 0.0f, 0.0f});
  case ViewController::Skeleton:
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
