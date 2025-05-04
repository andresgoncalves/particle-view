#ifndef DISPLAY_CONTROL_PANEL_H
#define DISPLAY_CONTROL_PANEL_H

#include <QtWidgets/QScrollArea>

#include "../../controllers/AppContext.h"

class DisplayControlPanel : public QScrollArea
{
public:
  DisplayControlPanel(AppContext &appContext, QWidget *parent);

private:
  AppContext &appContext;
};

#endif