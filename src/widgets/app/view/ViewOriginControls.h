#ifndef VIEW_ORIGIN_CONTROLS_H
#define VIEW_ORIGIN_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** View origin controls */
class ViewOriginControls : public Section
{
public:
  /** Creates the origin controls */
  ViewOriginControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewOriginControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif