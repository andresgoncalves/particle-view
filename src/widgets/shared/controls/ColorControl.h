#ifndef COLOR_CONTROL_H
#define COLOR_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QCheckBox>

#include <widgets/shared/buttons/ColorButton.h>

/** Color control with title and a color picker */
class ColorControl : public QWidget
{
public:
  /** Creates a vertical control without title */
  ColorControl(QWidget *parent = nullptr);
  /** Creates a vertical control with title */
  ColorControl(const char *title, QWidget *parent = nullptr);
  /** Creates a control with title and given direction */
  ColorControl(const char *title, bool withCheckBox, QWidget *parent = nullptr);

  /** Get checkbox */
  QCheckBox *getCheckBox() const;
  /** Get color button */
  ColorButton *getColorButton() const;

private:
  QCheckBox *checkBox;
  ColorButton *colorButton;
};

#endif