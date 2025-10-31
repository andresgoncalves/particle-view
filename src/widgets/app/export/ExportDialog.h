#ifndef EXPORT_DIALOG_H
#define EXPORT_DIALOG_H

#include <QtWidgets/QDialog>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/NumericControl.h>

class ExportDialog : public QDialog
{
public:
  ExportDialog(AppContext &appContext, QWidget *parent = nullptr);

private:
  AppContext &appContext;

  NumericControl *animationSpeedControl;
  NumericControl *framesPerSecondControl;
};

#endif