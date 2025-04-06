#ifndef PARTICLE_H
#define PARTICLE_H

#include <QtGui/QVector3D>

struct Particle
{
  float radius = 1.0f;
  QVector3D position = {0.0f, 0.0f, 0.0f};
  QVector3D color = {1.0f, 0.0f, 0.0f};
};

#endif