#include "AppWindow.h"

#include <QtWidgets/QDockWidget>
#include <QtCore/QTimer>

#include "layout/CenterPanel.h"
#include "layout/LeftPanel.h"
#include "layout/RightPanel.h"
#include "layout/BottomPanel.h"
#include "layout/MenuBar.h"
#include "layout/ToolBar.h"
#include "layout/StatusBar.h"

#define ANIMATION_INTERVAL 1.0 / 60.0

AppWindow::AppWindow(AppContext &appContext, QWidget *parent) : appContext{appContext}, QMainWindow{parent}
{
  // Add center panel
  auto centerPanel = new CenterPanel{appContext, this};
  setCentralWidget(centerPanel);

  // Add left panel
  auto leftPanel = new LeftPanel{appContext, this};
  auto leftDock = new QDockWidget{this, Qt::Widget};
  leftDock->setWidget(leftPanel);
  leftDock->setTitleBarWidget(new QWidget{leftDock});
  leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, leftDock);
  setCorner(Qt::Corner::BottomLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);

  // Add right panel
  auto rightPanel = new RightPanel{appContext, this};
  auto rightDock = new QDockWidget{this, Qt::Widget};
  rightDock->setWidget(rightPanel);
  rightDock->setTitleBarWidget(new QWidget{rightDock});
  rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, rightDock);
  setCorner(Qt::Corner::BottomRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);

  // Add bottom panel
  auto bottomPanel = new BottomPanel{appContext, this};
  auto bottomDock = new QDockWidget{this, Qt::Widget};
  bottomDock->setWidget(bottomPanel);
  bottomDock->setTitleBarWidget(new QWidget{bottomDock});
  bottomDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, bottomDock);

  // Add menu bar
  auto menuBar = new MenuBar{appContext, this};
  setMenuBar(menuBar);

  // Add tool bar
  auto toolBar = new ToolBar{appContext, this};
  addToolBar(toolBar);

  // Add menu bar
  auto statusBar = new StatusBar{appContext, this};
  setStatusBar(statusBar);

  // Set window size
  resize(800, 600);

  // Start animation
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [&]()
          { appContext.animationController.updateTime(); });

  // Add animation playing listener
  auto playingCallback = [=](bool playing)
  {
    if (playing)
      timer->start(ANIMATION_INTERVAL);
    else
      timer->stop();
  };
  appContext.animationController.playingObservable.subscribe(this, playingCallback, true);
}

AppWindow::~AppWindow()
{
  appContext.animationController.playingObservable.unsubscribe(this);
}
