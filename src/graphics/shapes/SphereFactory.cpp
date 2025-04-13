#include "SphereFactory.h"

SphereFactory::SphereFactory(int divisions) : divisions{divisions} {}

std::vector<float> SphereFactory::buildVertices()
{
  auto vertices = std::vector<float>{};

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

  return vertices;
}

std::vector<int> SphereFactory::buildIndices()
{
  auto indices = std::vector<int>{};

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

  return indices;
}

std::vector<int> SphereFactory::buildOutlineIndices()
{
  auto indices = std::vector<int>{};

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

  return indices;
}
