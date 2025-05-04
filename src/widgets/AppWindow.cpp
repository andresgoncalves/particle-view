#include "AppWindow.h"

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTabWidget>

#include "controls/SceneControlPanel.h"
#include "controls/DisplayControlPanel.h"

AppWindow::AppWindow(AppContext &appContext, QWidget *parent) : appContext{appContext}, QMainWindow{parent}
{

  auto sceneControlPanel = new SceneControlPanel{appContext, this};
  auto displayControlPanel = new DisplayControlPanel{appContext, this};

  auto leftTabs = new QTabWidget{this};
  leftTabs->addTab(sceneControlPanel, "Escena");
  leftTabs->addTab(displayControlPanel, "Visualización");

  auto leftDock = new QDockWidget{this, Qt::Widget};
  leftDock->setWidget(leftTabs);
  leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  leftDock->setTitleBarWidget(new QWidget{leftDock});

  appWidget = new AppWidget{appContext, this};

  addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, leftDock);
  setCentralWidget(appWidget);
  resize(800, 600);
}

AppWidget *AppWindow::getAppWidget()
{
  return appWidget;
}