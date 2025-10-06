#ifndef GRAPH_WINDOW_H
#define GRAPH_WINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtCharts/QChart>

#include <controllers/AppContext.h>

class GraphWindow : public QDialog
{
public:
  GraphWindow(const Graph &graph, AppContext &appContext, QWidget *parent = nullptr);

  QImage renderToImage(QSize size, const Graph &graph, AppContext &appContext) const;

private:
  void buildChart(QChart *chart, const Graph &graph, AppContext &appContext) const;

  const Graph &graph;
};

#endif