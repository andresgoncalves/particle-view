#ifndef RENDER_CONTROLLER_H
#define RENDER_CONTROLLER_H

#include <QtGui/QMatrix4x4>

class RenderController
{
public:
  RenderController();

  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);

  void translateX(float distance);
  void translateY(float distance);
  void translateZ(float distance);

  void scale(float scale);

  QMatrix4x4 getViewProjectionMatrix();

private:
  QMatrix4x4 viewProjectionMatrix;
};

#endif