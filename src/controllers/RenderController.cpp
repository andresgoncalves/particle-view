#include <algorithm>

#include "RenderController.h"

RenderController::RenderController() {}

void RenderController::rotate(const QVector3D &angles, ReferenceFrame referenceFrame)
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
}

void RenderController::translate(const QVector3D &vector, ReferenceFrame referenceFrame)
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
}

void RenderController::scale(float factor, ReferenceFrame referenceFrame)
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
}

void RenderController::setRotation(const QVector3D &angles)
{
  rotationAngles = angles;
};

void RenderController::setTranslation(const QVector3D &vector)
{
  translationVector = vector;
};

void RenderController::setScale(float factor)
{
  scaleFactor = std::clamp(factor, minScaleFactor, maxScaleFactor);
};

void RenderController::rotateX(float angle, ReferenceFrame referenceFrame)
{
  rotate({angle, 0.0f, 0.0f}, referenceFrame);
}

void RenderController::rotateY(float angle, ReferenceFrame referenceFrame)
{
  rotate({0.0f, angle, 0.0f}, referenceFrame);
}

void RenderController::rotateZ(float angle, ReferenceFrame referenceFrame)
{
  rotate({0.0f, 0.0f, angle}, referenceFrame);
}

void RenderController::translateX(float distance, ReferenceFrame referenceFrame)
{
  translate({distance, 0.0f, 0.0f}, referenceFrame);
}

void RenderController::translateY(float distance, ReferenceFrame referenceFrame)
{
  translate({0.0f, distance, 0.0f}, referenceFrame);
}

void RenderController::translateZ(float distance, ReferenceFrame referenceFrame)
{
  translate({0.0f, 0.0f, distance}, referenceFrame);
}

void RenderController::setRotationX(float angle)
{
  rotationAngles.setX(angle);
}

void RenderController::setRotationY(float angle)
{
  rotationAngles.setY(angle);
}

void RenderController::setRotationZ(float angle)
{
  rotationAngles.setZ(angle);
}

void RenderController::setTranslationX(float distance)
{
  translationVector.setX(distance);
}

void RenderController::setTranslationY(float distance)
{
  translationVector.setY(distance);
}

void RenderController::setTranslationZ(float distance)
{
  translationVector.setZ(distance);
}

void RenderController::setViewport(const QVector2D &scale)
{
  viewport = scale;
}

void RenderController::setOrigin(const QVector3D &origin)
{
  originVector = origin;
}

void RenderController::updateViewProjectionMatrix()
{
  viewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
}

QVector3D RenderController::getRotation() const
{
  return rotationAngles;
};

QVector3D RenderController::getTranslation() const
{
  return translationVector;
};

float RenderController::getScale() const
{
  return scaleFactor;
};

QVector2D RenderController::getViewport() const
{
  return viewport;
}

void RenderController::toggleParticles(int info)
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

QMatrix4x4 RenderController::getOriginMatrix() const
{
  auto origin = originVector;
  // origin.setY(0);

  auto originMatrix = QMatrix4x4{};
  originMatrix.translate(-origin);
  // originMatrix.translate({-3.68f * 0.1f, 0, -3.68f * 0.1f});
  return originMatrix;
}

QMatrix4x4 RenderController::getTranslationMatrix() const
{
  auto translationMatrix = QMatrix4x4{};
  translationMatrix.translate(translationVector);
  return translationMatrix;
}

QMatrix4x4 RenderController::getScaleMatrix() const
{
  auto scaleMatrix = QMatrix4x4{};
  scaleMatrix.scale(scaleFactor);
  return scaleMatrix;
}

QMatrix4x4 RenderController::getRotationMatrix() const
{
  auto rotationMatrix = QMatrix4x4{QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix()};
  return rotationMatrix;
}

QMatrix4x4 RenderController::getViewMatrix() const
{
  auto viewMatrix = QMatrix4x4{};
  viewMatrix.translate({0.0f, 0.0f, -1.0f});

  viewMatrix *= getTranslationMatrix() * getScaleMatrix() * (getOriginMatrix().inverted() * getRotationMatrix() * getOriginMatrix());

  return viewMatrix;
}

QMatrix4x4 RenderController::getProjectionMatrix() const
{
  return getProjectionMatrix(projectionMode);
}

QMatrix4x4 RenderController::getProjectionMatrix(ProjectionMode mode) const
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

QMatrix4x4 RenderController::getViewProjectionMatrix() const
{
  return viewProjectionMatrix;
}