#include "ArrowFactory.h"

ArrowFactory::ArrowFactory(int divisions) : divisions{divisions} {}

std::vector<float> ArrowFactory::buildVertices()
{
  auto vertices = std::vector<float>{};

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
    vertices.push_back(bodyHeight);
    vertices.push_back(z);
  }

  // Centro de la base del cono
  vertices.push_back(0.0f);
  vertices.push_back(bodyHeight);
  vertices.push_back(0.0f);

  // Vértices de la cabeza de la flecha (cono)
  for (int i = 0; i <= divisions; i++)
  {
    float angle = 2 * M_PI * i / divisions;
    float x = headRadius * std::cos(angle);
    float z = headRadius * std::sin(angle);
    vertices.push_back(x);
    vertices.push_back(bodyHeight);
    vertices.push_back(z);
  }
  // Punta del cono
  vertices.push_back(0.0f);
  vertices.push_back(bodyHeight + headHeight);
  vertices.push_back(0.0f);

  return vertices;
}

std::vector<int> ArrowFactory::buildIndices()
{
  auto bodyIndices = buildBodyIndices();
  auto headIndices = buildHeadIndices();

  bodyIndices.insert(bodyIndices.end(), headIndices.begin(), headIndices.end());

  return bodyIndices;
}

std::vector<int> ArrowFactory::buildBodyIndices()
{
  auto indices = std::vector<int>{};

  uint baseIndex = (divisions + 1) * 2;

  // Lados del cilindro
  for (int i = 0; i < divisions; i++)
  {
    int base1 = 2 * i;
    int base2 = 2 * (i + 1);
    int top1 = base1 + 1;
    int top2 = base2 + 1;

    indices.push_back(base1);
    indices.push_back(base2);
    indices.push_back(top1);

    indices.push_back(top1);
    indices.push_back(base2);
    indices.push_back(top2);
  }

  // Base del cilindro
  for (int i = 0; i < divisions; i++)
  {
    indices.push_back(baseIndex);
    indices.push_back(2 * i);
    indices.push_back(2 * (i + 1));
  }

  return indices;
}

std::vector<int> ArrowFactory::buildHeadIndices()
{
  auto indices = std::vector<int>{};

  uint baseIndex = (divisions + 1) * 2;
  uint tipIndex = (divisions + 1) * 3 + 1;

  // Base del cono
  for (int i = 1; i <= divisions; i++)
  {
    indices.push_back(baseIndex);
    indices.push_back(baseIndex + i);
    indices.push_back(baseIndex + i + 1);
  }

  // Lados del cono
  for (int i = 1; i <= divisions; i++)
  {
    indices.push_back(tipIndex);
    indices.push_back(baseIndex + i);
    indices.push_back(baseIndex + i + 1);
  }

  return indices;
}