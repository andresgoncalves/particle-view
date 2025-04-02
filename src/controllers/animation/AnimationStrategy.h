#ifndef ANIMATION_STRATEGY_H
#define ANIMATION_STRATEGY_H

#include "../../models/Story.h"
#include "../../models/Scene.h"

class AnimationStrategy
{
public:
  virtual ~AnimationStrategy() = default;

  virtual Scene getScene(const Story &story, double time) const = 0;
};

#endif