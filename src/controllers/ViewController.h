#ifndef RENDER_CONTROLLER_H
#define RENDER_CONTROLLER_H

#include <set>
#include <QtGui/QMatrix4x4>

#include "Observable.h"

class ViewController
{
public:
  enum ReferenceFrame
  {
    Model,
    Projection
  };

  enum ProjectionMode
  {
    Ortho,
    Perspective
  };

  enum ParticleShape
  {
    Solid,
    Skeleton,
  };

  ViewController();

  void rotate(const QVector3D &angles, ReferenceFrame referenceFrame = Model);
  void translate(const QVector3D &vector, ReferenceFrame referenceFrame = Model);
  void scale(float factor, ReferenceFrame referenceFrame = Model);

  void setOrigin(const QVector3D &origin);
  void setTranslation(const QVector3D &vector);
  void setRotation(const QVector3D &angles);
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

  void setOriginX(float distance);
  void setOriginY(float distance);
  void setOriginZ(float distance);

  void setViewport(const QVector2D &scale);

  void updateViewProjectionMatrix();

  QVector2D getViewport() const;
  QVector3D getRotation() const;
  QVector3D getTranslation() const;
  float getScale() const;

  QMatrix4x4 getScaleMatrix() const;
  QMatrix4x4 getRotationMatrix() const;
  QMatrix4x4 getTranslationMatrix() const;
  QMatrix4x4 getOriginMatrix() const;

  QMatrix4x4 getViewMatrix() const;
  QMatrix4x4 getProjectionMatrix() const;
  QMatrix4x4 getProjectionMatrix(ProjectionMode mode) const;
  QMatrix4x4 getViewProjectionMatrix() const;

  ProjectionMode projectionMode = Perspective;
  ParticleShape particleShape = Solid;

  float axisSize = 0.2f;

  void toggleParticles(int info);
  std::set<int> hiddenParticles;

  Observable<QVector3D> rotationObservable = rotationAngles;
  Observable<QVector3D> translationObservable = translationVector;
  Observable<QVector3D> originObservable = originVector;
  Observable<float> scaleObservable = scaleFactor;

private:
  QVector3D rotationAngles = {};
  QVector3D translationVector = {};
  QVector3D originVector = {};
  float scaleFactor = 1.0f;

  QVector2D viewport = {1.0f, 1.0f};

  QMatrix4x4 viewProjectionMatrix;

  float minScaleFactor = 1e-2f;
  float maxScaleFactor = 1e3f;
};

#endif