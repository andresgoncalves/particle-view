#ifndef RENDER_CONTROLLER_H
#define RENDER_CONTROLLER_H

#include <QtGui/QMatrix4x4>

class RenderController
{
public:
  enum ReferenceFrame
  {
    Model,
    Projection
  };

  RenderController();

  void rotate(const QVector3D &angles, ReferenceFrame referenceFrame = Model);
  void translate(const QVector3D &vector, ReferenceFrame referenceFrame = Model);
  void scale(float factor, ReferenceFrame referenceFrame = Model);

  void setRotation(const QVector3D &angles);
  void setTranslation(const QVector3D &vector);
  void setScale(float factor);

  void rotateX(float angle, ReferenceFrame referenceFrame = Model);
  void rotateY(float angle, ReferenceFrame referenceFrame = Model);
  void rotateZ(float angle, ReferenceFrame referenceFrame = Model);

  void translateX(float distance, ReferenceFrame referenceFrame = Model);
  void translateY(float distance, ReferenceFrame referenceFrame = Model);
  void translateZ(float distance, ReferenceFrame referenceFrame = Model);

  void setRotationX(float angle);
  void setRotationY(float angle);
  void setRotationZ(float angle);

  void setTranslationX(float distance);
  void setTranslationY(float distance);
  void setTranslationZ(float distance);

  void updateViewProjectionMatrix();

  QVector3D getRotation() const;
  QVector3D getTranslation() const;
  float getScale() const;

  QMatrix4x4 getRotationMatrix() const;
  QMatrix4x4 getViewProjectionMatrix() const;

private:
  QVector3D rotationAngles;
  QVector3D translationVector;
  float scaleFactor = 1.0f;

  QMatrix4x4 viewProjectionMatrix;

  const float minScaleFactor = 0.1f;
};

#endif