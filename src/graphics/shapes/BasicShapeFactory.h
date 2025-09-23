#ifndef BASIC_SHAPE_FACTORY_H
#define BASIC_SHAPE_FACTORY_H

#include <vector>

class BasicShapeFactory
{
public:
  virtual ~BasicShapeFactory() = default;

  /** Build shape vertices */
  virtual std::vector<float> buildVertices() const = 0;
  /** Build solid shape indices */
  virtual std::vector<int> buildIndices() const = 0;
  /** Build shape skeleton indices */
  virtual std::vector<int> buildOutlineIndices() const = 0;
};

#endif