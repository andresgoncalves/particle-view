#ifndef LINEAR_ANIMATION_STRATEGY_H
#define LINEAR_ANIMATION_STRATEGY_H

#include "AnimationStrategy.h"

class LinearAnimationStrategy : public AnimationStrategy
{
public:
  Scene getScene(const Story &story, double time) const override;
};

#endif