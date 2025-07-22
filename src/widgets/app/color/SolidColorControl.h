#ifndef SOLID_COLOR_CONTROL_H
#define SOLID_COLOR_CONTROL_H

#include <QtWidgets/QWidget>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/ColorControl.h>
#include <utils/color/SolidColorStrategy.h>

/** Color control */
class SolidColorControl : public QWidget
{
public:
  /** Creates a color control */
  SolidColorControl(AppContext &appContext, QWidget *parent = nullptr);

  /** Set color strategy */
  void setColorStrategy(SolidColorStrategy *colorStrategy);
  /** Get color strategy */
  std::shared_ptr<SolidColorStrategy> getColorStrategy() const;

private:
  /** Solid color value */
  QColor solidColor;

  /** Color control */
  ColorControl *colorControl;

  /** Application context */
  AppContext &appContext;
};

#endif