#ifndef DISPLAY_COLOR_CONTROLS_H
#define DISPLAY_COLOR_CONTROLS_H

#include <QtWidgets/QWidget>

#include "../ControlSection.h"
#include "../../../controllers/AppContext.h"

class DisplayColorControls : public ControlSection
{
public:
  DisplayColorControls(AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayColorControls();

private:
  AppContext &appContext;
};

#endif