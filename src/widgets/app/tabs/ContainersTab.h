#ifndef CONTAINERS_TAB_H
#define CONTAINERS_TAB_H

#include <QtWidgets/QScrollArea>

#include <controllers/AppContext.h>

/** Containers application controls */
class ContainersTab : public QScrollArea
{
public:
  /** Creates the display application controls,composed by:
   * - ContainerControls
   */
  ContainersTab(AppContext &appContext, QWidget *parent);

private:
  /** Application controls */
  AppContext &appContext;
};

#endif