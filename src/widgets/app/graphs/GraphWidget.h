#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QtWidgets/QWidget>

#include <controllers/graphs/Graph.h>
#include <models/Story.h>

class GraphWidget : public QWidget
{
public:
  GraphWidget(const Graph &graph, const Story &story, QWidget *parent = nullptr);
};

#endif