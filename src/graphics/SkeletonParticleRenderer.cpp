#include "SkeletonParticleRenderer.h"

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

SkeletonParticleRenderer::SkeletonParticleRenderer()
{
  loadShader();
  loadBuffers();
}

void SkeletonParticleRenderer::render(const Particle &particle, const RenderController &renderController)
{
  auto viewProjectionMatrix = renderController.getViewProjectionMatrix();

  auto nearPlane = viewProjectionMatrix.row(3) + viewProjectionMatrix.row(2);
  nearPlane /= nearPlane.toVector3D().length();

  if (QVector3D::dotProduct(nearPlane.toVector3D(), particle.position) + nearPlane.w() < particle.radius)
    return;

  auto modelMatrix = QMatrix4x4{};
  modelMatrix.translate(particle.position);
  modelMatrix.scale(particle.radius);

  auto modelViewProjectionMatrix = viewProjectionMatrix * modelMatrix;

  shaderProgram.bind();
  vertexArray.bind();

  shaderProgram.setUniformValue("color", particle.color);
  shaderProgram.setUniformValue("modelViewProjectionMatrix", modelViewProjectionMatrix);
  glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, nullptr);

  vertexArray.release();
  shaderProgram.release();
}

void SkeletonParticleRenderer::loadShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void SkeletonParticleRenderer::loadBuffers()
{
  vertexArray.create();
  vertexArray.bind();

  auto vertices = std::vector<float>{};
  loadVertices(vertices);

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(vertices[0]));

  auto indices = std::vector<uint>{};
  loadIndices(indices);

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(), indices.size() * sizeof(indices[0]));

  indexCount = indices.size();

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(vertices[0]), nullptr);

  vertexArray.release();
}

void SkeletonParticleRenderer::loadVertices(std::vector<float> &vertices, size_t divisions)
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

void SkeletonParticleRenderer::loadIndices(std::vector<uint> &indices, size_t divisions)
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