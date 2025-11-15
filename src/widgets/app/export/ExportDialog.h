#ifndef EXPORT_DIALOG_H
#define EXPORT_DIALOG_H

#include <QtWidgets/QDialog>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/NumericControl.h>

class ExportDialog : public QDialog
{
public:
  ExportDialog(AppContext &appContext, QWidget *parent = nullptr);

  float getAnimationSpeed() const;
  int getFramesPerSecond() const;
  QSize getSize() const;

private:
  AppContext &appContext;

  NumericControl *widthControl;
  NumericControl *heightControl;
  NumericControl *animationSpeedControl;
  NumericControl *framesPerSecondControl;
};

#endif