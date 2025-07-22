#ifndef ANIMATION_TIME_SLIDER_H
#define ANIMATION_TIME_SLIDER_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Animation time slider */
class AnimationTimeSlider : public Section
{
public:
  /** Creates the animation time slider */
  AnimationTimeSlider(AppContext &appContext, QWidget *parent = nullptr);
  ~AnimationTimeSlider();

private:
  /** Set if animation was playing before moving slider */
  bool wasPlaying;

  /** Application context */
  AppContext &appContext;
};

#endif