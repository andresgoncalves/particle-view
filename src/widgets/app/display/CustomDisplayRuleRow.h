#ifndef CUSTOM_DISPLAY_RULE_ROW_H
#define CUSTOM_DISPLAY_RULE_ROW_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>

class CustomDisplayRuleRow : public QWidget
{
public:
  CustomDisplayRuleRow(DisplayController::CustomRules::iterator displayRule, AppContext &appContext, QWidget *parent = nullptr);
};

#endif