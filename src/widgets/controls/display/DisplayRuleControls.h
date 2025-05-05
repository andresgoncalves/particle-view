#ifndef DISPLAY_RULE_CONTROLS_H
#define DISPLAY_RULE_CONTROLS_H

#include <QtWidgets/QWidget>

#include "../ControlSection.h"
#include "../../../controllers/AppContext.h"

class DisplayRuleControls : public ControlSection
{
public:
  DisplayRuleControls(AppContext &appContext, QWidget *parent = nullptr);
};

#endif