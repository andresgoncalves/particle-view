#ifndef GRAPH_CONTROLLER_H
#define GRAPH_CONTROLLER_H

#include <list>
#include <memory>

#include "Observable.h"

#include <controllers/graphs/Graph.h>

class GraphController
{
public:
  using Graphs = std::list<std::shared_ptr<Graph>>;

  GraphController();

  /** Get graphs */
  Graphs &getGraphs();

  /** Add a graph */
  Graphs::iterator addGraph(Graphs::value_type value);
  /** Replace a graph */
  void replaceGraph(Graphs::iterator it, Graphs::value_type value);
  /** Remove a graph */
  void removeGraph(Graphs::iterator it);
  /** Clear a graph */
  void clearGraphs();

  /** Graphs observable */
  BaseObservable<Graphs &> graphsObservable;

private:
  Graphs graphs;
};

#endif