#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>

#include "Scene.h"

struct Story
{
  std::map<double, Scene> scenes;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    double startTime;
    double endTime;
    std::map<std::string, float> maxValues;
    PropertyTypeMap particleProperties;
    PropertyTypeMap sceneProperties;
  } metadata;

  QVector3D getOrigin() const;
  float getBaseScale() const;
};

#endif