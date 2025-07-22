#ifndef ANIMATION_PLAY_CONTROLS_H
#define ANIMATION_PLAY_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Animation play controls */
class AnimationPlayControls : public Section
{
public:
  /** Creates the animation play controls */
  AnimationPlayControls(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationPlayControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif