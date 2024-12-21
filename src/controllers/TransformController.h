#ifndef Transform_CONTROLLER_H
#define Transform_CONTROLLER_H

#include <QtGui/QVector2D>

#include "RenderController.h"

class TransformController
{
public:
  enum TransformType
  {
    Translation,
    RotationXY,
    RotationZ,
    Scale
  };

  TransformController(RenderController *renderController);

  void start(const QVector2D &point);
  void move(const QVector2D &point, TransformType type);
  void end();

  void scroll(int delta);

  bool isTransforming() const;

private:
  void translate(const QVector2D &point);
  void rotateXY(const QVector2D &point);
  void rotateZ(const QVector2D &point);
  void scale(const QVector2D &point);

  bool transforming = false;
  QVector2D startPoint;
  QVector2D lastPoint;

  RenderController *renderController;

  const float rotationSensitivity = 300.0f;
  const float translationSensitivity = 1.0f;
  const float scaleSensitivity = 1.0f;
  const float scrollScaleSensitivity = 0.01f;
};

#endif