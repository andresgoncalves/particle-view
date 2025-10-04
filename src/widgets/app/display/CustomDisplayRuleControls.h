#ifndef CUSTOM_DISPLAY_RULE_CONTROLS_H
#define CUSTOM_DISPLAY_RULE_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

class CustomDisplayRuleControls : public Section
{
public:
  CustomDisplayRuleControls(AppContext &appContext, QWidget *parent = nullptr);
};

#endif