#ifndef STEP_ANIMATION_STRATEGY_H
#define STEP_ANIMATION_STRATEGY_H

#include "AnimationStrategy.h"

class StepAnimationStrategy : public AnimationStrategy
{
public:
  Scene getScene(const Story &story, double time) const override;
};

#endif