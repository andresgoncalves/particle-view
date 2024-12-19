#include "RenderController.h"

RenderController::RenderController() {}

void RenderController::rotateX(float angle)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{1.0f, 0.0f, 0.0f};
  viewProjectionMatrix.rotate(angle, vector);
}

void RenderController::rotateY(float angle)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{0.0f, 1.0f, 0.0f};
  viewProjectionMatrix.rotate(angle, vector);
}

void RenderController::rotateZ(float angle)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{0.0f, 0.0f, 1.0f};
  viewProjectionMatrix.rotate(angle, vector);
}

void RenderController::translateX(float distance)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{1.0f, 0.0f, 0.0f};
  viewProjectionMatrix.translate(distance * vector);
}

void RenderController::translateY(float distance)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{0.0f, 1.0f, 0.0f};
  viewProjectionMatrix.translate(distance * vector);
}

void RenderController::translateZ(float distance)
{
  auto vector = viewProjectionMatrix.inverted() * QVector3D{0.0f, 0.0f, 1.0f};
  viewProjectionMatrix.translate(distance * vector);
}

void RenderController::scale(float scale)
{
  viewProjectionMatrix *= scale;
}

QMatrix4x4 RenderController::getViewProjectionMatrix()
{
  return viewProjectionMatrix;
}