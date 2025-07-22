#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <QtWidgets/QMainWindow>

#include <controllers/AppContext.h>

/** Main application window */
class AppWindow : public QMainWindow
{
public:
  /**
   * Creates the main application window, composed by:
   * - CenterPanel
   * - LeftPanel
   * - RightPanel
   * - BottomPanel
   * - MenuBar
   * - ToolBar
   * - StatusBar
   */
  AppWindow(AppContext &appContext, QWidget *parent = nullptr);
  ~AppWindow();

private:
  /** Application context */
  AppContext &appContext;
};

#endif