#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QtGui/QVector3D>

#include "Particle.h"

struct Scene
{
  double time;
  std::vector<Particle> particles;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    float maxRadius;
    float maxVelocity;
  } metadata;
};

#endif