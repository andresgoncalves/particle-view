#ifndef COLOR_SCALE_CONTROL_H
#define COLOR_SCALE_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/ColorControl.h>
#include <widgets/shared/controls/NumericControl.h>
#include <widgets/shared/sections/Section.h>
#include <utils/color/ColorScaleStrategy.h>

/** Color control */
class ColorScaleControl : public QWidget
{
public:
  /** Creates a color control */
  ColorScaleControl(AppContext &appContext, QWidget *parent = nullptr);

  /** Set color strategy */
  void setColorStrategy(ColorScaleStrategy *colorStrategy);
  /** Get color strategy */
  std::shared_ptr<ColorScaleStrategy> getColorStrategy() const;

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

  /** Property combo box values */
  std::vector<std::pair<std::string, VectorComponent>> propertyValues;

  /** Application context */
  AppContext &appContext;
};

#endif