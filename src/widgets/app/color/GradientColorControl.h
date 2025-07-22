#ifndef GRADIENT_COLOR_CONTROL_H
#define GRADIENT_COLOR_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/ColorControl.h>
#include <widgets/shared/controls/NumericControl.h>
#include <widgets/shared/sections/Section.h>
#include <utils/color/GradientColorStrategy.h>

/** Color control */
class GradientColorControl : public QWidget
{
public:
  /** Creates a color control */
  GradientColorControl(AppContext &appContext, QWidget *parent = nullptr);

  /** Set color strategy */
  void setColorStrategy(GradientColorStrategy *colorStrategy);
  /** Get color strategy */
  std::shared_ptr<GradientColorStrategy> getColorStrategy() const;

private:
  /** Start color */
  QColor startColor;
  /** End color */
  QColor endColor;

  /** Property combo box */
  QComboBox *propertyComboBox;
  /** Start color control */
  ColorControl *startColorControl;
  /** End color control */
  ColorControl *endColorControl;
  /** Start value control */
  NumericControl *startValueControl;
  /** End value control */
  NumericControl *endValueControl;

  /** Application context */
  AppContext &appContext;
};

#endif