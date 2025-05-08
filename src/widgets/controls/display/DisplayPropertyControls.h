#ifndef DISPLAY_PROPERTY_CONTROLS_H
#define DISPLAY_PROPERTY_CONTROLS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>

#include "../ControlSection.h"
#include "../../../controllers/AppContext.h"

class DisplayPropertyControls : public ControlSection
{
public:
  DisplayPropertyControls(AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayPropertyControls();

private:
  void refreshProperties();

  QCheckBox *particleCheckBox;
  std::map<std::string, QCheckBox *> vectorCheckBoxes;
  AppContext &appContext;
};

#endif