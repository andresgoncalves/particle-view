#include <algorithm>

#include "ViewController.h"

ViewController::ViewController() {}

void ViewController::rotate(const QVector3D &angles, ReferenceFrame referenceFrame)
{
  switch (referenceFrame)
  {
  case Model:
    rotationAngles += angles;
    break;
  case Projection:
  {
    auto currentRotationMatrix = QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix();
    auto newRotationMatrix = QQuaternion::fromEulerAngles(angles).toRotationMatrix();

    rotationAngles = QQuaternion::fromRotationMatrix(newRotationMatrix * currentRotationMatrix).toEulerAngles();
    break;
  }
  }
  rotationObservable.notify();
}

void ViewController::translate(const QVector3D &vector, ReferenceFrame referenceFrame)
{
  switch (referenceFrame)
  {
  case Model:
    translationVector += getViewProjectionMatrix().inverted().mapVector(vector);
    break;
  case Projection:
    translationVector += vector;
    break;
  }
  translationObservable.notify();
}

void ViewController::scale(float factor, ReferenceFrame referenceFrame)
{
  switch (referenceFrame)
  {
  case Model:
    scaleFactor += factor;
    break;
  case Projection:
    scaleFactor *= factor;
    break;
  }

  scaleFactor = std::clamp(scaleFactor, minScaleFactor, maxScaleFactor);
  scaleObservable.notify();
}

void ViewController::setRotation(const QVector3D &angles)
{
  rotationAngles = angles;
  rotationObservable.notify();
};

void ViewController::setTranslation(const QVector3D &vector)
{
  translationVector = vector;
  translationObservable.notify();
};

void ViewController::setScale(float factor)
{
  scaleFactor = std::clamp(factor, minScaleFactor, maxScaleFactor);
  scaleObservable.notify();
};

void ViewController::rotateX(float angle, ReferenceFrame referenceFrame)
{
  rotate({angle, 0.0f, 0.0f}, referenceFrame);
}

void ViewController::rotateY(float angle, ReferenceFrame referenceFrame)
{
  rotate({0.0f, angle, 0.0f}, referenceFrame);
}

void ViewController::rotateZ(float angle, ReferenceFrame referenceFrame)
{
  rotate({0.0f, 0.0f, angle}, referenceFrame);
}

void ViewController::translateX(float distance, ReferenceFrame referenceFrame)
{
  translate({distance, 0.0f, 0.0f}, referenceFrame);
}

void ViewController::translateY(float distance, ReferenceFrame referenceFrame)
{
  translate({0.0f, distance, 0.0f}, referenceFrame);
}

void ViewController::translateZ(float distance, ReferenceFrame referenceFrame)
{
  translate({0.0f, 0.0f, distance}, referenceFrame);
}

void ViewController::setRotationX(float angle)
{
  rotationAngles.setX(angle);
  rotationObservable.notify();
}

void ViewController::setRotationY(float angle)
{
  rotationAngles.setY(angle);
  rotationObservable.notify();
}

void ViewController::setRotationZ(float angle)
{
  rotationAngles.setZ(angle);
  rotationObservable.notify();
}

void ViewController::setTranslationX(float distance)
{
  translationVector.setX(distance);
  translationObservable.notify();
}

void ViewController::setTranslationY(float distance)
{
  translationVector.setY(distance);
  translationObservable.notify();
}

void ViewController::setTranslationZ(float distance)
{
  translationVector.setZ(distance);
  translationObservable.notify();
}

void ViewController::setViewport(const QVector2D &scale)
{
  viewport = scale;
}

void ViewController::setOrigin(const QVector3D &origin)
{
  originVector = origin;
  originObservable.notify();
}

void ViewController::updateViewProjectionMatrix()
{
  viewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
}

QVector3D ViewController::getRotation() const
{
  return rotationAngles;
};

QVector3D ViewController::getTranslation() const
{
  return translationVector;
};

float ViewController::getScale() const
{
  return scaleFactor;
};

QVector2D ViewController::getViewport() const
{
  return viewport;
}

void ViewController::toggleParticles(int info)
{
  if (hiddenParticles.find(info) != hiddenParticles.end())
  {
    hiddenParticles.erase(info);
  }
  else
  {
    hiddenParticles.insert(info);
  }
}

QMatrix4x4 ViewController::getOriginMatrix() const
{
  auto origin = originVector;
  // origin.setY(0);

  auto originMatrix = QMatrix4x4{};
  originMatrix.translate(-origin);
  // originMatrix.translate({-3.68f * 0.1f, 0, -3.68f * 0.1f});
  return originMatrix;
}

QMatrix4x4 ViewController::getTranslationMatrix() const
{
  auto translationMatrix = QMatrix4x4{};
  translationMatrix.translate(translationVector);
  return translationMatrix;
}

QMatrix4x4 ViewController::getScaleMatrix() const
{
  auto scaleMatrix = QMatrix4x4{};
  scaleMatrix.scale(scaleFactor);
  return scaleMatrix;
}

QMatrix4x4 ViewController::getRotationMatrix() const
{
  auto rotationMatrix = QMatrix4x4{QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix()};
  return rotationMatrix;
}

QMatrix4x4 ViewController::getViewMatrix() const
{
  auto viewMatrix = QMatrix4x4{};
  viewMatrix.translate({0.0f, 0.0f, -1.0f});

  viewMatrix *= getTranslationMatrix() * getScaleMatrix() * (getOriginMatrix().inverted() * getRotationMatrix() * getOriginMatrix());

  return viewMatrix;
}

QMatrix4x4 ViewController::getProjectionMatrix() const
{
  return getProjectionMatrix(projectionMode);
}

QMatrix4x4 ViewController::getProjectionMatrix(ProjectionMode mode) const
{
  auto projectionMatrix = QMatrix4x4{};
  switch (mode)
  {
  case Ortho:
    projectionMatrix.ortho(-viewport.x(), viewport.x(), -viewport.y(), viewport.y(), 0.1f, 100.0f);
    break;
  case Perspective:
    projectionMatrix.perspective(45.0f, viewport.x() / viewport.y(), 0.1f, 100.0f);
    break;
  }
  return projectionMatrix;
}

QMatrix4x4 ViewController::getViewProjectionMatrix() const
{
  return viewProjectionMatrix;
}