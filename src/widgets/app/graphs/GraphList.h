#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include <controllers/AppContext.h>

#include "GraphRow.h"

class GraphList : public QWidget
{
public:
  GraphList(AppContext &appContext, QWidget *parent = nullptr);

private:
  void build(GraphController::Graphs &graphs);
  void clear();

  QVBoxLayout *itemLayout;
  std::list<GraphRow *> rows;

  AppContext &appContext;
};

#endif