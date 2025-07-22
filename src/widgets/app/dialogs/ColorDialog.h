#ifndef COLOR_DIALOG_H
#define COLOR_DIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/app/color/SolidColorControl.h>
#include <widgets/app/color/GradientColorControl.h>
#include <utils/color/ColorStrategy.h>

/** Color dialog */
class ColorDialog : public QDialog
{
public:
  /**
   * Creates a color dialog
   */
  ColorDialog(AppContext &appContext, QWidget *parent = nullptr);

  /** Set color strategy */
  void setColorStrategy(ColorStrategy *colorStrategy) const;
  /** Get color strategy */
  std::shared_ptr<ColorStrategy> getColorStrategy() const;

private:
  /** Color strategy combo box */
  QComboBox *colorStrategyComboBox;
  /** Solid color controls */
  SolidColorControl *solidColorControls;
  /** Gradient color controls */
  GradientColorControl *gradientColorControls;

  /** Application context */
  AppContext &appContext;
};

#endif