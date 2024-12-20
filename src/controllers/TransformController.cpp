#include "TransformController.h"

TransformController::TransformController(RenderController *renderController) : renderController{renderController} {}

void TransformController::start(QVector2D point)
{
  transforming = true;
  startPoint = lastPoint = point;
}

void TransformController::move(QVector2D point, TransformType type)
{
  switch (type)
  {
  case RotationXY:
    rotateXY(point);
    break;
  case RotationZ:
    rotateZ(point);
    break;
  case Translation:
    translate(point);
    break;
  case Scale:
    scale(point);
    break;
  }
}

void TransformController::end()
{
  transforming = false;
}

void TransformController::scroll(int delta)
{
  auto scaleFactor = delta * scrollScaleSensitivity;

  renderController->scale(scaleFactor, RenderController::Model);
}

void TransformController::translate(QVector2D point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto translation = distance * translationSensitivity;

  renderController->translate({translation.x(), translation.y(), 0.0f}, RenderController::Projection);
}

void TransformController::rotateXY(QVector2D point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto rotation = distance * rotationSensitivity;

  renderController->rotate({rotation.y(), -rotation.x(), 0.0f}, RenderController::Projection);
}

void TransformController::rotateZ(QVector2D point)
{
  float startAngle = atan2(lastPoint.y(), lastPoint.x());

  lastPoint = point;

  float endAngle = atan2(point.y(), point.x());

  float rotation = (endAngle - startAngle) * 180.0f / M_PI;

  renderController->rotateZ(rotation, RenderController::Projection);
}

void TransformController::scale(QVector2D point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto scaleFactor = distance.y() * scaleSensitivity;

  renderController->scale(scaleFactor, RenderController::Model);
}

bool TransformController::isTransforming() const
{
  return transforming;
}