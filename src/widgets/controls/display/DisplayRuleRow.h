#ifndef DISPLAY_RULE_ROW
#define DISPLAY_RULE_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

#include "../../../controllers/display/DisplayRule.h"

class DisplayRuleRow : public QWidget
{
public:
  DisplayRuleRow(std::shared_ptr<DisplayRule> displayRule, QWidget *parent = nullptr);
  ~DisplayRuleRow();

private:
  std::shared_ptr<DisplayRule> displayRule;
};

#endif