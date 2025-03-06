#ifndef TRANSFORM_MODES_WIDGET_H
#define TRANSFORM_MODES_WIDGET_H

#include <functional>

#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "../../controllers/TransformController.h"

class TransformModesWidget : public QWidget
{
public:
  TransformModesWidget(TransformController &transformController, QWidget *parent = nullptr);
  ~TransformModesWidget();

private:
  QLabel *label;
  QPushButton *rotateXYButton;
  QPushButton *rotateZButton;
  QPushButton *translateXYButton;
  QPushButton *translateZButton;
  QPushButton *scaleButton;

  TransformController &transformController;

  std::function<void(TransformController::TransformType)> transformTypeCallback;
};

#endif