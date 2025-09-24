#ifndef CONTAINER_LIST_H
#define CONTAINER_LIST_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>

#include <controllers/AppContext.h>

#include "ContainerRow.h"

class ContainerList : public QWidget
{
public:
  ContainerList(AppContext &appContext, QWidget *parent = nullptr);

private:
  void build(ContainerController::Containers &containers);
  void clear();

  QVBoxLayout *itemLayout;
  std::list<ContainerRow *> rows;

  AppContext &appContext;
};

#endif