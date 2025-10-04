#ifndef DISPLAY_TAB_H
#define DISPLAY_TAB_H

#include <QtWidgets/QScrollArea>

#include <controllers/AppContext.h>

/** Display application controls */
class DisplayTab : public QScrollArea
{
public:
  /** Creates the display application controls,composed by:
   * - DisplayPropertyControls
   * - CustomDisplayRuleControls
   */
  DisplayTab(AppContext &appContext, QWidget *parent);

private:
  /** Application controls */
  AppContext &appContext;
};

#endif