#ifndef VIEW_ROTATION_CONTROLS_H
#define VIEW_ROTATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** View rotation controls */
class ViewRotationControls : public Section
{
public:
  /** Creates the rotation controls */
  ViewRotationControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewRotationControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif