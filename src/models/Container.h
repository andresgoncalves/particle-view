#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>

#include <QtGui/QColor>
#include <QtGui/QVector3D>
#include <QtGui/QQuaternion>

enum class ContainerShape
{
  Cuboid,
  Ellipsoid
};

struct Container
{
  std::string name;
  QVector3D center;
  QVector3D size;
  QQuaternion rotation;
  ContainerShape shape;
  QColor color = QColor{255, 255, 255};
  bool enabled = true;
};

#endif