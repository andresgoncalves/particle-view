#ifndef CONTAINER_CONTROLS_H
#define CONTAINER_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

class ContainerControls : public Section
{
public:
  ContainerControls(AppContext &appContext, QWidget *parent = nullptr);
};

#endif