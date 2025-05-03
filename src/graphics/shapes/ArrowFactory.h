#ifndef ARROW_FACTORY_H
#define ARROW_FACTORY_H

#include <vector>

class ArrowFactory
{
public:
  ArrowFactory(int divisions);

  std::vector<float> buildVertices();
  std::vector<int> buildIndices();
  std::vector<int> buildBodyIndices();
  std::vector<int> buildHeadIndices();

  float bodyRadius = 0.05f;
  float headRadius = 0.10f;
  float headHeight = 0.25f;
  float bodyHeight = 0.75f;

private:
  int divisions;
};

#endif