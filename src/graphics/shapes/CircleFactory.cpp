#include "CircleFactory.h"

#include <cmath>

CircleFactory::CircleFactory(int divisions) : divisions{divisions} {}

std::vector<float> CircleFactory::buildVertices() const
{
  auto vertices = std::vector<float>{};

  vertices.push_back(0);
  vertices.push_back(0);
  vertices.push_back(0);

  for (int index = 0; index <= divisions; index++)
  {
    float theta = 2.0f * index * M_PI / divisions;
    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);

    vertices.push_back(cosTheta);
    vertices.push_back(sinTheta);
    vertices.push_back(0.0f);
  }

  return vertices;
}

std::vector<int> CircleFactory::buildIndices() const
{
  auto indices = std::vector<int>{};

  for (int index = 1; index <= divisions; index++)
  {
    indices.push_back(0);
    indices.push_back(index);
    indices.push_back(index + 1);
  }
  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(divisions);

  return indices;
}

std::vector<int> CircleFactory::buildOutlineIndices() const
{
  auto indices = std::vector<int>{};

  for (int index = 1; index <= divisions; index++)
  {
    indices.push_back(index);
    indices.push_back(index + 1);
  }
  indices.push_back(divisions);
  indices.push_back(1);

  return indices;
}
