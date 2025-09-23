#ifndef CONTAINER_H
#define CONTAINER_H

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
  /** Container center */
  QVector3D center;
  /** Container size */
  QVector3D size;
  /** Container rotation */
  QQuaternion rotation;
  /** Container shape */
  ContainerShape shape;
  /** Container color */
  QColor color;
  /** True if this container is enabled */
  bool enabled = true;
};

#endif