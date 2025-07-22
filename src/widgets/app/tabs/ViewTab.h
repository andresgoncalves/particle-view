#ifndef VIEW_TAB_H
#define VIEW_TAB_H

#include <QtWidgets/QScrollArea>

#include <controllers/AppContext.h>

/** View application controls */
class ViewTab : public QScrollArea
{
public:
  /** Creates the view application controls, composed by:
   * - ViewOriginControls
   * - ViewTranslationControls
   * - ViewRotationControls
   * - ViewScaleControls
   */
  ViewTab(AppContext &appContext, QWidget *parent);

private:
  /** Application controls */
  AppContext &appContext;
};

#endif