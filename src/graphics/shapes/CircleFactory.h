#ifndef CIRCLE_FACTORY_H
#define CIRCLE_FACTORY_H

#include <vector>

#include "BasicShapeFactory.h"

class CircleFactory : public BasicShapeFactory
{
public:
  CircleFactory(int divisions);

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