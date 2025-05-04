#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <vector>

#include "Scene.h"

struct Story
{
  std::map<double, Scene> scenes;
  std::vector<std::string> customProperties;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    float maxRadius;
    float maxVelocity;
  } metadata;
};

#endif