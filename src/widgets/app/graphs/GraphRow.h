#ifndef GRAPH_ROW_H
#define GRAPH_ROW_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>

class GraphRow : public QWidget
{
public:
  GraphRow(GraphController::Graphs::iterator displayRule, AppContext &appContext, QWidget *parent = nullptr);
};

#endif