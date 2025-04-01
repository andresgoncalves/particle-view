#include "AppWindow.h"

#include <QtWidgets/QDockWidget>

#include "controls/SceneControlPanel.h"

AppWindow::AppWindow(AppContext &appContext, QWidget *parent) : appContext{appContext}, QMainWindow{parent}
{

  auto sceneControlPanel = new SceneControlPanel{appContext, this};
  auto sceneControlPanelDock = new QDockWidget{this, Qt::Widget};
  sceneControlPanelDock->setWidget(sceneControlPanel);
  sceneControlPanelDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  sceneControlPanelDock->setTitleBarWidget(new QWidget{sceneControlPanelDock});

  appWidget = new AppWidget{appContext, this};

  addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, sceneControlPanelDock);
  setCentralWidget(appWidget);
  resize(800, 600);
}

AppWidget *AppWindow::getAppWidget()
{
  return appWidget;
}