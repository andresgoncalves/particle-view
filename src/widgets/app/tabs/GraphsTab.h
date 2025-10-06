#ifndef GRAPHS_TAB_H
#define GRAPHS_TAB_H

#include <QtWidgets/QScrollArea>

#include <controllers/AppContext.h>

/** Graphs application controls */
class GraphsTab : public QScrollArea
{
public:
  /** Creates the graph application controls */
  GraphsTab(AppContext &appContext, QWidget *parent);

private:
  /** Application controls */
  AppContext &appContext;
};

#endif