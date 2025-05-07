#ifndef DISPLAY_RULE_ROW_H
#define DISPLAY_RULE_ROW_H

#include <functional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include "../../../controllers/AppContext.h"

class DisplayRuleRow : public QWidget
{
public:
  DisplayRuleRow(std::shared_ptr<DisplayRule> displayRule, AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayRuleRow();

  void setDisplayRule(std::shared_ptr<DisplayRule> displayRule);

  void onEdit(std::function<void()> editCallback) const;

private:
  std::shared_ptr<DisplayRule> displayRule;
  QLabel *label;
  QCheckBox *checkBox;
  QPushButton *editButton;
};

#endif