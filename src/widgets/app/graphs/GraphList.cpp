#include "GraphList.h"

#include <QtWidgets/QVBoxLayout>

GraphList::GraphList(AppContext &appContext, QWidget *parent) : appContext{appContext}, QWidget{parent}
{
  itemLayout = new QVBoxLayout{this};
  itemLayout->setAlignment(Qt::AlignTop);
  itemLayout->setSpacing(0);
  itemLayout->setContentsMargins({});

  build(appContext.graphController.getGraphs());

  appContext.graphController.graphsObservable.subscribe(
      this,
      [this](GraphController::Graphs &graphs)
      {
        clear();
        build(graphs);
      });
}

void GraphList::build(GraphController::Graphs &graphs)
{
  for (auto it = graphs.begin(); it != graphs.end(); it++)
  {
    auto row = new GraphRow{it, appContext, this};
    rows.push_back(row);
    itemLayout->addWidget(row);
  }
}

void GraphList::clear()
{
  for (auto row : rows)
  {
    itemLayout->removeWidget(row);
    row->deleteLater();
  }
  rows.clear();
}
