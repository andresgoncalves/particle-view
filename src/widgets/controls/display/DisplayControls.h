#ifndef DISPLAY_CONTROLS_H
#define DISPLAY_CONTROLS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>

#include "../ControlSection.h"
#include "../../../controllers/AppContext.h"

class DisplayControls : public ControlSection
{
public:
  DisplayControls(AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayControls();

private:
  void refreshProperties();

  QCheckBox *particleCheckBox;
  std::map<std::string, QCheckBox *> vectorCheckBoxes;
  AppContext &appContext;
};

#endif