#include "TransformController.h"

TransformController::TransformController(RenderController &renderController) : renderController{renderController} {}

void TransformController::start(const QVector2D &point)
{
  transforming = true;
  startPoint = lastPoint = point;
}

void TransformController::move(const QVector2D &point)
{
  switch (transformType.get())
  {
  case RotationXY:
    rotateXY(point);
    break;
  case RotationZ:
    rotateZ(point);
    break;
  case TranslationXY:
    translateXY(point);
    break;
  case TranslationZ:
    translateZ(point);
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

  renderController.scale(scaleFactor, RenderController::Model);
}

void TransformController::translateXY(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto translation = distance * translationSensitivity;

  renderController.translate({translation.x(), translation.y(), 0.0f}, RenderController::Projection);
}

void TransformController::translateZ(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto translation = distance.y() * translationSensitivity;

  renderController.translate({0.0f, 0.0f, translation}, RenderController::Projection);
}

void TransformController::rotateXY(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto rotation = distance * rotationSensitivity;

  renderController.rotate({-rotation.y(), rotation.x(), 0.0f}, RenderController::Projection);
}

void TransformController::rotateZ(const QVector2D &point)
{
  float startAngle = atan2(lastPoint.y(), lastPoint.x());

  lastPoint = point;

  float endAngle = atan2(point.y(), point.x());

  float rotation = (endAngle - startAngle) * 180.0f / M_PI;

  renderController.rotateZ(rotation, RenderController::Projection);
}

void TransformController::scale(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto scaleFactor = distance.y() * scaleSensitivity;

  renderController.scale(scaleFactor, RenderController::Model);
}

bool TransformController::isTransforming() const
{
  return transforming;
}