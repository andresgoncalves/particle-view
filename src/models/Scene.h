#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QtGui/QVector3D>

#include "Particle.h"

struct Scene
{
  Scene();

  std::vector<Particle> particles;

  QVector3D geometryStart;
  QVector3D geometryEnd;
};

#endif