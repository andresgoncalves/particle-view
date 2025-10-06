#include "GraphController.h"

GraphController::GraphController()
{
}

GraphController::Graphs &GraphController::getGraphs()
{
  return graphs;
}

GraphController::Graphs::iterator GraphController::addGraph(Graphs::value_type graph)
{
  graphs.push_back(graph);
  graphsObservable.notify(graphs);
  return std::prev(graphs.end());
}

void GraphController::replaceGraph(Graphs::iterator it, Graphs::value_type graph)
{
  *it = graph;
  graphsObservable.notify(graphs);
}

void GraphController::removeGraph(Graphs::iterator it)
{
  graphs.erase(it);
  graphsObservable.notify(graphs);
}

void GraphController::clearGraphs()
{
  graphs.clear();
  graphsObservable.notify(graphs);
}
