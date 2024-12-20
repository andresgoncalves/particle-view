#include "AxisRenderer.h"

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

void AxisRenderer::render(const Axis &axis, const RenderController &renderController)
{
  auto modelMatrix = QMatrix4x4{};
  auto color = QVector3D{};

  switch (axis)
  {
  case Axis::X:
    modelMatrix.rotate(-90.0f, {0.0f, 0.0f, 1.0f});
    color = {1.0f, 0.0f, 0.0f};
    break;
  case Axis::Y:
    color = {0.0f, 1.0f, 0.0f};
    break;
  case Axis::Z:
    modelMatrix.rotate(-90.0f, {1.0f, 0.0f, 0.0f});
    color = {0.0f, 0.0f, 1.0f};
    break;
  }

  modelMatrix.scale(0.2f);

  auto translationMatrix = QMatrix4x4{};
  translationMatrix.translate({-0.8f, -0.8f, 0.0f});

  auto modelViewProjectionMatrix = translationMatrix * renderController.getRotationMatrix() * modelMatrix;

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

void AxisRenderer::loadVertices(std::vector<float> &vertices, size_t divisions)
{
  float bodyRadius = 0.05f;
  float headRadius = 0.1f;
  float headHeight = 0.25f;
  float height = 1.0 - headHeight;

  // Generar vértices del cilindro (eje de la flecha)
  for (int i = 0; i <= divisions; i++)
  {
    float angle = 2 * i * M_PI / divisions;
    float x = bodyRadius * std::cos(angle);
    float z = bodyRadius * std::sin(angle);

    // Base del cilindro
    vertices.push_back(x);
    vertices.push_back(0.0f);
    vertices.push_back(z);
    // Top del cilindro
    vertices.push_back(x);
    vertices.push_back(height);
    vertices.push_back(z);
  }

  // Centro de la base del cono
  vertices.push_back(0.0f);
  vertices.push_back(height);
  vertices.push_back(0.0f);
  int baseIndex = vertices.size() / 3 - 1;

  // Vértices de la cabeza de la flecha (cono)
  for (int i = 0; i <= divisions; i++)
  {
    float angle = 2 * M_PI * i / divisions;
    float x = headRadius * std::cos(angle);
    float z = headRadius * std::sin(angle);
    vertices.push_back(x);
    vertices.push_back(height);
    vertices.push_back(z);
  }
  // Punta del cono
  vertices.push_back(0.0f);
  vertices.push_back(height + headHeight);
  vertices.push_back(0.0f);
}

void AxisRenderer::loadIndices(std::vector<uint> &indices, size_t divisions)
{
  uint baseIndex = (divisions + 1) * 2;
  uint tipIndex = (divisions + 1) * 3 + 1;

  // Generar índices del cilindro
  for (int i = 0; i < divisions; i++)
  {
    int base1 = 2 * i;
    int base2 = 2 * (i + 1);
    int top1 = base1 + 1;
    int top2 = base2 + 1;

    // Lados del cilindro
    indices.push_back(base1);
    indices.push_back(base2);
    indices.push_back(top1);

    indices.push_back(top1);
    indices.push_back(base2);
    indices.push_back(top2);
  }

  // Generar índices del cilindro
  for (int i = 0; i < divisions; i++)
  {
    int base1 = 2 * i;
    int base2 = 2 * (i + 1);
    int top1 = base1 + 1;
    int top2 = base2 + 1;

    // Lados del cilindro
    indices.push_back(base1);
    indices.push_back(base2);
    indices.push_back(top1);

    indices.push_back(top1);
    indices.push_back(base2);
    indices.push_back(top2);
  }

  for (int i = 0; i < divisions; i++)
  {
    indices.push_back(baseIndex);
    indices.push_back(2 * i);
    indices.push_back(2 * (i + 1));
  }

  // Índices de la base del cono
  for (int i = 1; i <= divisions; i++)
  {
    indices.push_back(baseIndex);
    indices.push_back(baseIndex + i);
    indices.push_back(baseIndex + i + 1);
  }

  // Índices de los lados del cono
  for (int i = 1; i <= divisions; i++)
  {
    indices.push_back(tipIndex);
    indices.push_back(baseIndex + i);
    indices.push_back(baseIndex + i + 1);
  }
}