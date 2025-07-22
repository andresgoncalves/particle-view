#include "ColorPicker.h"

std::optional<QColor> ColorPicker::getColor(QWidget *parent)
{
  return getColor(QColor{0, 0, 0}, parent);
}

std::optional<QColor> ColorPicker::getColor(QColor color, QWidget *parent)
{
  // Create picker
  auto dialog = new ColorPicker{color, parent};

  // Execute picker
  std::optional<QColor> result = std::nullopt;
  if (dialog->exec() == QDialog::Accepted)
    result = dialog->currentColor();

  // Delete picker
  dialog->deleteLater();

  // Return result
  return result;
}

ColorPicker::ColorPicker(QColor color, QWidget *parent) : QColorDialog{color, parent}
{
  setOption(ColorPicker::ShowAlphaChannel, true);
}