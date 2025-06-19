#include "DisplayRuleGrid.h"

#include <QtWidgets/QVBoxLayout>

#include "DisplayRuleDialog.h"

DisplayRuleGrid::DisplayRuleGrid(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  itemLayout = new QVBoxLayout{this};
  itemLayout->setAlignment(Qt::AlignTop);
  itemLayout->setSpacing(0);
  itemLayout->setContentsMargins({});

  auto displayRules = appContext.displayController.getDisplayRules();
  for (auto displayRule = displayRules.begin(); displayRule != displayRules.end(); displayRule++)
    addRow(displayRule);
}

void DisplayRuleGrid::addRow(DisplayController::DisplayRules::iterator displayRuleIterator)
{
  auto row = new DisplayRuleRow{*displayRuleIterator, appContext, this};
  rows.push_back(row);
  itemLayout->addWidget(row);

  auto rowIterator = std::prev(rows.end());
  auto editCallback = [=, this]
  {
    if (auto binaryDisplayRule = dynamic_cast<AbstractBinaryDisplayRule *>((*displayRuleIterator).get()))
    {
      auto displayRuleDialog = new DisplayRuleDialog{*binaryDisplayRule, appContext, this};
      switch (displayRuleDialog->exec())
      {
      case DisplayRuleDialog::DialogResult::Accept:
        appContext.displayController.replaceDisplayRule(displayRuleIterator, displayRuleDialog->getDisplayRule());
        row->setDisplayRule(*displayRuleIterator);
        break;
      case DisplayRuleDialog::DialogResult::Delete:
        removeRow(rowIterator);
        appContext.displayController.removeDisplayRule(displayRuleIterator);
        break;
      }
      displayRuleDialog->deleteLater();
    }
  };
  row->onEdit(editCallback);
}

void DisplayRuleGrid::removeRow(std::list<DisplayRuleRow *>::iterator it)
{
  itemLayout->removeWidget(*it);
  (*it)->deleteLater();
  rows.erase(it);
}

void DisplayRuleGrid::clear()
{

  for (auto it = rows.begin(); it != rows.end(); it++)
  {
    itemLayout->removeWidget(*it);
    (*it)->deleteLater();
  }
  rows.clear();
}
