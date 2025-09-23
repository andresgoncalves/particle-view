#include "CubeFactory.h"

CubeFactory::CubeFactory() {}

std::vector<float> CubeFactory::buildVertices() const
{
  auto vertices = std::vector<float>{
      -1.0f, -1.0f, -1.0f, // 0
      1.0f, -1.0f, -1.0f,  // 1
      1.0f, 1.0f, -1.0f,   // 2
      -1.0f, 1.0f, -1.0f,  // 3
      -1.0f, -1.0f, 1.0f,  // 4
      1.0f, -1.0f, 1.0f,   // 5
      1.0f, 1.0f, 1.0f,    // 6
      -1.0f, 1.0f, 1.0f    // 7
  };

  return vertices;
}

std::vector<int> CubeFactory::buildIndices() const
{
  auto indices = std::vector<int>{
      // Back face
      0, 1, 2, 2, 3, 0,
      // Front face
      4, 5, 6, 6, 7, 4,
      // Left face
      0, 3, 7, 7, 4, 0,
      // Right face
      1, 5, 6, 6, 2, 1,
      // Bottom face
      0, 1, 5, 5, 4, 0,
      // Top face
      3, 2, 6, 6, 7, 3};

  return indices;
}

std::vector<int> CubeFactory::buildOutlineIndices() const
{
  auto indices = std::vector<int>{
      // Bottom square
      0, 1,
      1, 2,
      2, 3,
      3, 0,
      // Top square
      4, 5,
      5, 6,
      6, 7,
      7, 4,
      // Vertical edges
      0, 4,
      1, 5,
      2, 6,
      3, 7};

  return indices;
}
