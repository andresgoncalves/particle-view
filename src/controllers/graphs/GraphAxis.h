#ifndef GRAPH_AXIS_H
#define GRAPH_AXIS_H

#include <string>
#include <optional>

#include <models/Scene.h>

template <typename T>
class GraphAxis
{
public:
  virtual ~GraphAxis() = default;

  /** Get scene value with current axis */
  virtual std::optional<T> getValue(const Scene &scene) const = 0;

  /** Get axis text */
  virtual std::string getText() const = 0;
};

#endif