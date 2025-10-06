#ifndef GRAPH_AXIS_H
#define GRAPH_AXIS_H

#include <string>
#include <optional>

#include <models/Scene.h>

class GraphAxis
{
public:
  virtual ~GraphAxis() = default;

  /** Get scene value with current axis */
  virtual std::optional<float> getValue(const Scene &scene) const = 0;

  /** Get axis text */
  virtual std::string getText() const = 0;

  void setRange(std::pair<float, float> range)
  {
    this->range = range;
  }

  std::pair<float, float> getRange() const
  {
    return range;
  }

private:
  std::pair<float, float> range;
};

#endif