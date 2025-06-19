#ifndef DISPLAY_RULE_GRID_H
#define DISPLAY_RULE_GRID_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include "DisplayRuleRow.h"
#include "../../../controllers/AppContext.h"

class DisplayRuleGrid : public QWidget
{
public:
  DisplayRuleGrid(AppContext &appContext, QWidget *parent = nullptr);

  void addRow(DisplayController::DisplayRules::iterator displayRule);
  void clear();

private:
  void removeRow(std::list<DisplayRuleRow *>::iterator it);

  QVBoxLayout *itemLayout;
  std::list<DisplayRuleRow *> rows;

  AppContext &appContext;
};

#endif