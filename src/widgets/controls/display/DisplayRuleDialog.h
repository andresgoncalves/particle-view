#ifndef DISPLAY_RULE_DIALOG_H
#define DISPLAY_RULE_DIALOG_H

#include <string>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>

#include "../NumericControl.h"
#include "../../../controllers/AppContext.h"

class DisplayRuleDialog : public QDialog
{
public:
  enum DisplayRuleItem
  {
    Equal,
    NotEqual,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
  };

  DisplayRuleDialog(AppContext &appContext, QWidget *parent = nullptr);

  std::shared_ptr<DisplayRule> getDisplayRule() const;

private:
  QComboBox *propertyComboBox;
  QComboBox *ruleComboBox;
  NumericControl *valueControl;
};

#endif