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
  enum DialogResult
  {
    Cancel = QDialog::Rejected,
    Accept = QDialog::Accepted,
    Delete,
  };

  enum DisplayRuleType
  {
    Equal,
    NotEqual,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
  };

  DisplayRuleDialog(AppContext &appContext, QWidget *parent = nullptr);
  DisplayRuleDialog(AbstractBinaryDisplayRule &displayRule, AppContext &appContext, QWidget *parent = nullptr);

  std::shared_ptr<DisplayRule> getDisplayRule() const;

private:
  DisplayRuleDialog(bool edit, AppContext &appContext, QWidget *parent = nullptr);

  QComboBox *propertyComboBox;
  QComboBox *ruleComboBox;
  QLineEdit *colorTextField;
  NumericControl *valueControl;
};

#endif