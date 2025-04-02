#include "StepAnimationStrategy.h"

Scene StepAnimationStrategy::getScene(const Story &story, double time) const
{
  if (story.scenes.empty())
    return Scene{};

  auto next = story.scenes.lower_bound(time);

  if (next == story.scenes.begin())
    return next->second;

  auto prev = std::prev(next);

  return prev->second;
}
