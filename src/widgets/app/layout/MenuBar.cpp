#include "MenuBar.h"

#include <widgets/app/menu/FileMenu.h>

MenuBar::MenuBar(AppContext &appContext, QWidget *parent) : appContext{appContext}, QMenuBar{parent}
{
  auto fileMenu = new FileMenu{appContext, this};

  addMenu(fileMenu);
}