#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <set>

#include "Scene.h"

struct Story
{
  std::map<double, Scene> scenes;
  std::map<std::string, PropertyType> particleProperties;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    double startTime;
    double endTime;
    std::map<std::string, float> maxValues;
  } metadata;

  QVector3D getOrigin() const;
  float getBaseScale() const;
};

#endif