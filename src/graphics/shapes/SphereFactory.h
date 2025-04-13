#ifndef SPHERE_FACTORY_H
#define SPHERE_FACTORY_H

#include <vector>

class SphereFactory
{
public:
  SphereFactory(int divisions);

  std::vector<float> buildVertices();
  std::vector<int> buildIndices();
  std::vector<int> buildOutlineIndices();

  float radius = 1.0f;

private:
  int divisions;
};

#endif