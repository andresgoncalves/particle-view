#ifndef FILE_MENU_H
#define FILE_MENU_H

#include <QtWidgets/QMenu>

#include <controllers/AppContext.h>

/**
 * Application file menu
 */
class FileMenu : public QMenu
{
public:
  FileMenu(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;
};

#endif