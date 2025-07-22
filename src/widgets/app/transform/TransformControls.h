#ifndef TRANSFORM_CONTROLS_H
#define TRANSFORM_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** Transform controls */
class TransformControls : public Section
{
public:
  /** Creates the transform controls */
  TransformControls(AppContext &appContext, QWidget *parent = nullptr);
  ~TransformControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif