#ifndef ANIMATION_TAB_H
#define ANIMATION_TAB_H

#include <QtWidgets/QScrollArea>

#include <controllers/AppContext.h>

/** Animation application controls */
class AnimationTab : public QScrollArea
{
public:
  /** Creates the animation application controls, composed by:
   * - AnimationTimeControls
   * - AnimationStrategyControls
   */
  AnimationTab(AppContext &appContext, QWidget *parent);

private:
  /** Application controls */
  AppContext &appContext;
};

#endif