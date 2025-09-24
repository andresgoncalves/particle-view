#ifndef SPHERE_FACTORY_H
#define SPHERE_FACTORY_H

#include <vector>

#include "BasicShapeFactory.h"

class SphereFactory : public BasicShapeFactory
{
public:
  SphereFactory(int divisions);

  /** Build cube vertices */
  std::vector<float> buildVertices() const override;
  /** Build solid cube indices */
  std::vector<int> buildIndices() const override;
  /** Build cube skeleton indices */
  std::vector<int> buildOutlineIndices() const override;

private:
  int divisions;
};

#endif