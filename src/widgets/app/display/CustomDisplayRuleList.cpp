#include "CustomDisplayRuleList.h"

#include <QtWidgets/QVBoxLayout>

CustomDisplayRuleList::CustomDisplayRuleList(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  itemLayout = new QVBoxLayout{this};
  itemLayout->setAlignment(Qt::AlignTop);
  itemLayout->setSpacing(0);
  itemLayout->setContentsMargins({});

  build(appContext.displayController.getCustomRules());

  appContext.displayController.customRulesObservable.subscribe(
      this,
      [this](DisplayController::CustomRules &customRules)
      {
        clear();
        build(customRules);
      });
}

void CustomDisplayRuleList::build(DisplayController::CustomRules &customRules)
{
  for (auto it = customRules.begin(); it != customRules.end(); it++)
  {
    auto row = new CustomDisplayRuleRow{it, appContext, this};
    rows.push_back(row);
    itemLayout->addWidget(row);
  }
}

void CustomDisplayRuleList::clear()
{
  for (auto row : rows)
  {
    itemLayout->removeWidget(row);
    row->deleteLater();
  }
  rows.clear();
}
