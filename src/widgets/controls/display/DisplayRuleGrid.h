#ifndef DISPLAY_RULE_GRID
#define DISPLAY_RULE_GRID

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include "DisplayRuleRow.h"
#include "../../../controllers/AppContext.h"

class DisplayRuleGrid : public QWidget
{
public:
  DisplayRuleGrid(AppContext &appContext, QWidget *parent = nullptr);

  void addDisplayRule(std::shared_ptr<DisplayRule> rule);
  void removeRow(std::list<DisplayRuleRow *>::iterator it);

private:
  QVBoxLayout *itemLayout;
  std::list<DisplayRuleRow *> rows;

  AppContext &appContext;
};

#endif