#include <algorithm>

#include "RenderController.h"

RenderController::RenderController() {}

void RenderController::rotate(QVector3D angles, ReferenceFrame referenceFrame)
{
  if (referenceFrame == Projection)
  {
    auto currentRotationMatrix = QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix();
    auto newRotationMatrix = QQuaternion::fromEulerAngles(angles).toRotationMatrix();

    rotationAngles = QQuaternion::fromRotationMatrix(newRotationMatrix * currentRotationMatrix).toEulerAngles();
  }
  else
  {
    rotationAngles += angles;
  }
}

void RenderController::translate(QVector3D vector, ReferenceFrame referenceFrame)
{
  if (referenceFrame == Projection)
  {
    translationVector += scaleFactor * getRotationMatrix().inverted().mapVector(vector);
  }
  else
  {
    translationVector += vector;
  }
}

void RenderController::scale(float factor, ReferenceFrame referenceFrame)
{
  if (referenceFrame == Projection)
  {
    scaleFactor *= factor;
  }
  else
  {
    scaleFactor += factor;
  }
  scaleFactor = std::max(scaleFactor, minScaleFactor);
}

void RenderController::setRotation(QVector3D angles)
{
  rotationAngles = angles;
};

void RenderController::setTranslation(QVector3D vector)
{
  translationVector = vector;
};

void RenderController::setScale(float factor)
{
  scaleFactor = std::max(factor, minScaleFactor);
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

void RenderController::updateViewProjectionMatrix()
{
  /* Rotate */
  viewProjectionMatrix = getRotationMatrix();
  /* Translate */
  viewProjectionMatrix.translate(translationVector);
  /* Scale */
  viewProjectionMatrix.scale(scaleFactor);
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

QMatrix4x4 RenderController::getRotationMatrix() const
{
  return QMatrix4x4{QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix()};
}

QMatrix4x4 RenderController::getViewProjectionMatrix() const
{
  return viewProjectionMatrix;
}