#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <set>

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
    float maxRadius;
    float maxVelocity;
    std::map<std::string, float> largestScalars;
    std::map<std::string, float> largestVectors;
  } metadata;
};

#endif