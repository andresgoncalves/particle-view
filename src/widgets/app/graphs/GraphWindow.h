#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <optional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>

#include <controllers/AppContext.h>

class GraphWindow : public QDialog
{
public:
  GraphWindow(const Graph &graph, AppContext &appContext, QWidget *parent = nullptr);

private:
  const Graph &graph;
};

#endif