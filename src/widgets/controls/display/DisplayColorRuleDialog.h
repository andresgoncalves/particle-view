#ifndef DISPLAY_COLOR_RULE_DIALOG_H
#define DISPLAY_COLOR_RULE_DIALOG_H

#include <string>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>

#include "../NumericControl.h"
#include "../../../controllers/AppContext.h"

class DisplayColorRuleDialog : public QDialog
{
public:
  enum DialogResult
  {
    Cancel = QDialog::Rejected,
    Accept = QDialog::Accepted,
    Delete,
  };

  DisplayColorRuleDialog(AppContext &appContext, QWidget *parent = nullptr);
  DisplayColorRuleDialog(std::shared_ptr<ColorRule> colorRule, AppContext &appContext, QWidget *parent = nullptr);

  std::shared_ptr<ColorRule> getColorRule() const;

private:
  QComboBox *propertyComboBox;
  NumericControl *startValueControl;
  NumericControl *endValueControl;
  QLineEdit *endColorTextField;
  QLineEdit *startColorTextField;
};

#endif