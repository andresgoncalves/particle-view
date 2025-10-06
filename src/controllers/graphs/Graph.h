#ifndef GRAPH_H
#define GRAPH_H

#include "GraphAxis.h"

#include <optional>
#include <string>

class Graph
{
public:
  Graph(
      std::shared_ptr<GraphAxis> xAxis,
      std::shared_ptr<GraphAxis> yAxis) : Graph{"", xAxis, yAxis} {}

  Graph(
      std::string title,
      std::shared_ptr<GraphAxis> xAxis,
      std::shared_ptr<GraphAxis> yAxis) : title{title}, xAxis{xAxis}, yAxis{yAxis} {}

  void setTitle(std::string title)
  {
    this->title = title;
  }

  std::string getTitle() const
  {
    return title;
  }

  std::shared_ptr<GraphAxis> getXAxis() const
  {
    return xAxis;
  }

  std::shared_ptr<GraphAxis> getYAxis() const
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
  std::string title;
  std::shared_ptr<GraphAxis> xAxis;
  std::shared_ptr<GraphAxis> yAxis;
};

#endif