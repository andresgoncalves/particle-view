#ifndef TRANSFORM_CONTROLLER_H
#define TRANSFORM_CONTROLLER_H

#include <QtGui/QVector2D>

#include "ViewController.h"
#include "Observable.h"

class TransformController
{
public:
  enum TransformType
  {
    Translation,
    Rotation,
    Scale
  };

  TransformController(ViewController &viewController);

  void start(const QVector2D &point);
  void move(const QVector2D &point, bool alt = false);
  void end();

  void scroll(int delta);

  bool isTransforming() const;

  void setTransformType(TransformType transformType);
  TransformType getTransformType() const;

  Observable<TransformType> transformTypeObservable = transformType;

private:
  void translateXY(const QVector2D &point);
  void translateZ(const QVector2D &point);
  void rotateXY(const QVector2D &point);
  void rotateZ(const QVector2D &point);
  void scale(const QVector2D &point);

  bool transforming = false;
  QVector2D startPoint;
  QVector2D lastPoint;
  TransformType transformType = TransformType::Rotation;

  ViewController &viewController;

  const float rotationSensitivity = 300.0f;
  const float translationSensitivity = 1.0f;
  const float scaleSensitivity = 1.0f;
  const float scrollScaleSensitivity = 0.005f;
};

#endif