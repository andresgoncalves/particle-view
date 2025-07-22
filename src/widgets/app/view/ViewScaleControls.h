#ifndef VIEW_SCALE_CONTROLS_H
#define VIEW_SCALE_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** View scale controls */
class ViewScaleControls : public Section
{
public:
  /** Creates the scale controls */
  ViewScaleControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewScaleControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif