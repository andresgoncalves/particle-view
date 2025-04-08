#ifndef PARTICLE_H
#define PARTICLE_H

#include <map>
#include <QtGui/QVector3D>

struct Particle
{
  QVector3D position = {0.0f, 0.0f, 0.0f};
  QVector3D velocity = {0.0f, 0.0f, 0.0f};
  float radius = 1.0f;

  std::map<std::string, float> customProperties;
};

#endif