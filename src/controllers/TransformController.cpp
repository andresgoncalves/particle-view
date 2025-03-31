#include "TransformController.h"

TransformController::TransformController(ViewController &viewController) : viewController{viewController} {}

void TransformController::start(const QVector2D &point)
{
  transforming = true;
  startPoint = lastPoint = point;
}

void TransformController::move(const QVector2D &point)
{
  switch (transformType)
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

  viewController.scale(scaleFactor, ViewController::Model);
}

void TransformController::translateXY(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto translation = distance * translationSensitivity;

  viewController.translate({translation.x(), translation.y(), 0.0f}, ViewController::Projection);
}

void TransformController::translateZ(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto translation = distance.y() * translationSensitivity;

  viewController.translate({0.0f, 0.0f, translation}, ViewController::Projection);
}

void TransformController::rotateXY(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto rotation = distance * rotationSensitivity;

  viewController.rotate({-rotation.y(), rotation.x(), 0.0f}, ViewController::Projection);
}

void TransformController::rotateZ(const QVector2D &point)
{
  float startAngle = atan2(lastPoint.y(), lastPoint.x());

  lastPoint = point;

  float endAngle = atan2(point.y(), point.x());

  float rotation = (endAngle - startAngle) * 180.0f / M_PI;

  viewController.rotateZ(rotation, ViewController::Projection);
}

void TransformController::scale(const QVector2D &point)
{
  auto distance = point - lastPoint;

  lastPoint = point;

  auto scaleFactor = distance.y() * scaleSensitivity;

  viewController.scale(scaleFactor, ViewController::Model);
}

bool TransformController::isTransforming() const
{
  return transforming;
}

void TransformController::setTransformType(TransformController::TransformType transformType)
{
  this->transformType = transformType;
  transformTypeObservable.notify();
}

TransformController::TransformType TransformController::getTransformType() const
{
  return transformType;
}