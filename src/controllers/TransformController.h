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
    TranslationXY,
    TranslationZ,
    RotationXY,
    RotationZ,
    Scale
  };

  TransformController(ViewController &viewController);

  void start(const QVector2D &point);
  void move(const QVector2D &point);
  void end();

  void scroll(int delta);

  bool isTransforming() const;

  Observable<TransformType> transformType = TransformType::RotationXY;

private:
  void translateXY(const QVector2D &point);
  void translateZ(const QVector2D &point);
  void rotateXY(const QVector2D &point);
  void rotateZ(const QVector2D &point);
  void scale(const QVector2D &point);

  bool transforming = false;
  QVector2D startPoint;
  QVector2D lastPoint;

  ViewController &viewController;

  const float rotationSensitivity = 300.0f;
  const float translationSensitivity = 1.0f;
  const float scaleSensitivity = 1.0f;
  const float scrollScaleSensitivity = 0.01f;
};

#endif