#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>

#include <QtGui/QVector3D>

#include "Particle.h"

struct Scene
{
  int frame;
  double time;
  std::vector<Particle> particles;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    std::map<std::string, float> maxValues;
    PropertyTypeMap particleProperties;
  } metadata;
};

#endif