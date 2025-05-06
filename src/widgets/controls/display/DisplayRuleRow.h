#ifndef DISPLAY_RULE_ROW
#define DISPLAY_RULE_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#include "../../../controllers/AppContext.h"

class DisplayRuleRow : public QWidget
{
public:
  DisplayRuleRow(DisplayController::DisplayRules::iterator displayRule, AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayRuleRow();

private:
  DisplayController::DisplayRules::iterator displayRule;
};

#endif