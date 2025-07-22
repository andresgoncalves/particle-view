#ifndef DISPLAY_PROPERTY_CONTROLS_H
#define DISPLAY_PROPERTY_CONTROLS_H

#include <map>
#include <string>

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <widgets/shared/controls/ColorControl.h>
#include <controllers/AppContext.h>

/** Display property controls */
class DisplayPropertyControls : public Section
{
public:
  /** Creates the display property controls */
  DisplayPropertyControls(AppContext &appContext, QWidget *parent = nullptr);
  ~DisplayPropertyControls();

private:
  /** Map of checkbox widgets */
  std::map<std::string, ColorControl *> vectorColorControls;

  /** Application context */
  AppContext &appContext;
};

#endif