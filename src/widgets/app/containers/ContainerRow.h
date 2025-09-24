#ifndef CONTAINER_ROW_H
#define CONTAINER_ROW_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>

class ContainerRow : public QWidget
{
public:
  ContainerRow(ContainerController::Containers::iterator container, AppContext &appContext, QWidget *parent = nullptr);
};

#endif