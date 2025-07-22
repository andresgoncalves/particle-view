#include "LeftPanel.h"

#include <widgets/app/tabs/ViewTab.h>
#include <widgets/app/tabs/AnimationTab.h>
#include <widgets/app/tabs/DisplayTab.h>

LeftPanel::LeftPanel(AppContext &appContext, QWidget *parent) : appContext{appContext}, QTabWidget{parent}
{
  // View tab
  auto viewTab = new ViewTab{appContext, this};
  addTab(viewTab, "Vista");

  // Animation tab
  auto animationTab = new AnimationTab{appContext, this};
  addTab(animationTab, "Animación");

  // Display tab
  auto displayTab = new DisplayTab{appContext, this};
  addTab(displayTab, "Visualización");
}