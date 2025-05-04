#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <set>

#include "Scene.h"

struct Story
{
  std::map<double, Scene> scenes;
  std::vector<std::string> scalarProperties;
  std::vector<std::string> vectorProperties;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    float maxRadius;
    float maxVelocity;
  } metadata;
};

#endif