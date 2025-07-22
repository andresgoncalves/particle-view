#ifndef COLOR_BUTTON_H
#define COLOR_BUTTON_H

#include <QtGui/QColor>
#include <QtGui/QBrush>
#include <QtGui/QPaintEvent>
#include <QtWidgets/QPushButton>

#include <utils/color/ColorStrategy.h>

/** Color button */
class ColorButton : public QPushButton
{
public:
  /** Creates a color button */
  ColorButton(QWidget *parent = nullptr);

  /** Set solid color */
  void setSolidColor(QColor color);

  /** Set gradient color */
  void setColorScale(QColor start, QColor stop);

  /** Set color strategy */
  void setColorStrategy(ColorStrategy *colorStrategy);

protected:
  /** Paint widget */
  void paintEvent(QPaintEvent *) override;

private:
  QBrush brush;
};

#endif