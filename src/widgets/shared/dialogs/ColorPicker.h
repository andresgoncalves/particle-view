#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <optional>

#include <QtWidgets/QColorDialog>

/** Color picker */
class ColorPicker : public QColorDialog
{
public:
  /** Creates a color picker and returns selected color */
  static std::optional<QColor> getColor(QWidget *parent = nullptr);
  /** Creates a color picker and returns selected color */
  static std::optional<QColor> getColor(QColor color, QWidget *parent = nullptr);

  /** Creates a color picker */
  ColorPicker(QColor color, QWidget *parent = nullptr);
};

#endif