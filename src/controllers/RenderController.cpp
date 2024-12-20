#include "RenderController.h"

RenderController::RenderController() {}

void RenderController::rotate(QVector3D angles, ReferenceFrame referenceFrame)
{
  dirtyViewProjectionMatrix = true;
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
  dirtyViewProjectionMatrix = true;
  if (referenceFrame == Projection)
  {
    auto currentRotationMatrix = QMatrix4x4{QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix()};

    translationVector += scaleFactor * currentRotationMatrix.inverted().mapVector(vector);
  }
  else
  {
    translationVector += vector;
  }
}

void RenderController::scale(float factor, ReferenceFrame referenceFrame)
{
  dirtyViewProjectionMatrix = true;
  if (referenceFrame == Projection)
  {
    scaleFactor *= factor;
  }
  else
  {
    scaleFactor += factor;
  }
}

void RenderController::setRotation(QVector3D angles)
{
  dirtyViewProjectionMatrix = true;
  rotationAngles = angles;
};

void RenderController::setTranslation(QVector3D vector)
{
  dirtyViewProjectionMatrix = true;
  translationVector = vector;
};

void RenderController::setScale(float factor)
{
  dirtyViewProjectionMatrix = true;
  scaleFactor = factor;
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
  dirtyViewProjectionMatrix = true;
  rotationAngles.setX(angle);
}

void RenderController::setRotationY(float angle)
{
  dirtyViewProjectionMatrix = true;
  rotationAngles.setY(angle);
}

void RenderController::setRotationZ(float angle)
{
  dirtyViewProjectionMatrix = true;
  rotationAngles.setZ(angle);
}

void RenderController::setTranslationX(float distance)
{
  dirtyViewProjectionMatrix = true;
  translationVector.setX(distance);
}

void RenderController::setTranslationY(float distance)
{
  dirtyViewProjectionMatrix = true;
  translationVector.setY(distance);
}

void RenderController::setTranslationZ(float distance)
{
  dirtyViewProjectionMatrix = true;
  translationVector.setZ(distance);
}

QVector3D RenderController::getRotation()
{
  return rotationAngles;
};

QVector3D RenderController::getTranslation()
{
  return translationVector;
};

float RenderController::getScale()
{
  return scaleFactor;
};

QMatrix4x4 RenderController::getViewProjectionMatrix()
{
  if (dirtyViewProjectionMatrix)
  {
    dirtyViewProjectionMatrix = false;

    /* Rotate */
    viewProjectionMatrix = QMatrix4x4{QQuaternion::fromEulerAngles(rotationAngles).toRotationMatrix()};
    /* Translate */
    viewProjectionMatrix.translate(translationVector);
    /* Scale */
    viewProjectionMatrix.scale(scaleFactor);
  }

  return viewProjectionMatrix;
}