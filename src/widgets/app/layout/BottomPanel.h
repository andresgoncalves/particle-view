#ifndef BOTTOM_PANEL_H
#define BOTTOM_PANEL_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>

/**
 * Application bottom panel
 */
class BottomPanel : public QWidget
{
public:
  /** Creates the center panel, composed by:
   * - AnimationTimeSlider
   * - AnimationPlayControls
   */
  BottomPanel(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif