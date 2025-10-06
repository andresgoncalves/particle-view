#ifndef GRAPH_H
#define GRAPH_H

#include "GraphAxis.h"

#include <optional>

class Graph
{
public:
  Graph(
      std::shared_ptr<GraphAxis<float>> xAxis,
      std::shared_ptr<GraphAxis<float>> yAxis) : xAxis{xAxis}, yAxis{yAxis} {}

  std::shared_ptr<GraphAxis<float>> getXAxis() const
  {
    return xAxis;
  }

  std::shared_ptr<GraphAxis<float>> getYAxis() const
  {
    return yAxis;
  }

  std::optional<std::pair<float, float>> getValue(const Scene &scene) const
  {
    auto xValue = xAxis->getValue(scene);
    auto yValue = yAxis->getValue(scene);
    if (xValue.has_value() && yValue.has_value())
      return {{xValue.value(), yValue.value()}};
    return std::nullopt;
  }

private:
  std::shared_ptr<GraphAxis<float>> xAxis;
  std::shared_ptr<GraphAxis<float>> yAxis;
};

#endif