#ifndef GRAPH_CONTROLS_H
#define GRAPH_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

class GraphControls : public Section
{
public:
  GraphControls(AppContext &appContext, QWidget *parent = nullptr);
};

#endif