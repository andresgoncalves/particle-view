#include "LinearAnimationStrategy.h"

Scene LinearAnimationStrategy::getScene(const Story &story, double time) const
{
  if (story.scenes.empty())
    return Scene{};

  auto next = story.scenes.lower_bound(time);

  if (next == story.scenes.begin() || next->first == time)
    return next->second;

  auto prev = std::prev(next);

  if (next == story.scenes.end())
    return prev->second;

  double ratio = (time - prev->first) / (next->first - prev->first);

  auto scene = Scene{};

  for (
      auto prevIt = prev->second.particles.begin(), nextIt = next->second.particles.begin();
      prevIt != prev->second.particles.end() && nextIt != next->second.particles.end();
      ++prevIt, ++nextIt)
  {
    auto particle = *prevIt;
    particle.position = prevIt->position + (nextIt->position - prevIt->position) * ratio;
    scene.particles.push_back(particle);
  }

  return scene;
}
