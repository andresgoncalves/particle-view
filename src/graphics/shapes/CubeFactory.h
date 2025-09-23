#ifndef CUBE_FACTORY_H
#define CUBE_FACTORY_H

#include <vector>

#include "BasicShapeFactory.h"

class CubeFactory : public BasicShapeFactory
{
public:
  CubeFactory();

  /** Build cube vertices */
  std::vector<float> buildVertices() const override;
  /** Build solid cube indices */
  std::vector<int> buildIndices() const override;
  /** Build cube skeleton indices */
  std::vector<int> buildOutlineIndices() const override;
};

#endif