#ifndef VECTOR_CONTROL_H
#define VECTOR_CONTROL_H

#include <functional>
#include <array>

#include <QtGui/QVector3D>
#include <QtWidgets/QWidget>

#include "Control.h"
#include "NumericControl.h"

/** Vector control with title and a line edit */
class VectorControl : public Control<>
{
public:
  /** Creates a vertical control with no title and default subtitles */
  VectorControl(QWidget *parent = nullptr);

  /** Creates a vertical control with custom title and default subtitles */
  VectorControl(const char *title, QWidget *parent = nullptr);

  /** Creates a vertical control with no title custom subtitles */
  VectorControl(std::array<const char *, 3> subtitles, QWidget *parent = nullptr);

  /** Creates a vertical control with custom title and subtitles */
  VectorControl(const char *title, std::array<const char *, 3> subtitles, QWidget *parent = nullptr);

  /** Set which components should be visible */
  void setVisibleComponents(std::array<bool, 3> components);

  /** Set control value */
  void setValue(QVector3D value);

  /** Get control value */
  QVector3D getValue() const;

  /** Add change listener */
  void onChange(std::function<void(QVector3D)> callback) const;

  /** Get control widgets */
  std::array<NumericControl *, 3> getControls() const;

private:
  std::array<NumericControl *, 3> controls;
};

#endif