#include "DisplayRuleGrid.h"

#include <QtWidgets/QVBoxLayout>

DisplayRuleGrid::DisplayRuleGrid(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  itemLayout = new QVBoxLayout{this};
  itemLayout->setAlignment(Qt::AlignTop);
  itemLayout->setSpacing(0);
  itemLayout->setContentsMargins({});

  auto displayRules = appContext.displayController.getDisplayRules();
  for (auto ruleIt = displayRules.begin(); ruleIt != displayRules.end(); ruleIt++)
  {
    auto row = new DisplayRuleRow{ruleIt, appContext, this};
    rows.push_back(row);
    auto rowIt = std::prev(rows.end());
    itemLayout->addWidget(row);

    auto deleteCallback = [=, &appContext, this]
    {
      removeRow(rowIt);
      appContext.displayController.removeDisplayRule(ruleIt);
    };
  }
}

void DisplayRuleGrid::addDisplayRule(std::shared_ptr<DisplayRule> displayRule)
{
  auto ruleIt = appContext.displayController.addDisplayRule(displayRule);

  auto row = new DisplayRuleRow{ruleIt, appContext, this};
  rows.push_back(row);
  auto rowIt = std::prev(rows.end());
  itemLayout->addWidget(row);

  auto deleteCallback = [=, this]
  {
    removeRow(rowIt);
    appContext.displayController.removeDisplayRule(ruleIt);
  };
}

void DisplayRuleGrid::removeRow(std::list<DisplayRuleRow *>::iterator it)
{
  itemLayout->removeWidget(*it);
  (*it)->deleteLater();
  rows.erase(it);
}
