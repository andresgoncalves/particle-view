#ifndef CUSTOM_DISPLAY_RULE_LIST_H
#define CUSTOM_DISPLAY_RULE_LIST_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include <controllers/AppContext.h>

#include "CustomDisplayRuleRow.h"

class CustomDisplayRuleList : public QWidget
{
public:
  CustomDisplayRuleList(AppContext &appContext, QWidget *parent = nullptr);

private:
  void build(DisplayController::CustomRules &containers);
  void clear();

  QVBoxLayout *itemLayout;
  std::list<CustomDisplayRuleRow *> rows;

  AppContext &appContext;
};

#endif