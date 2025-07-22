#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <set>

#include "Scene.h"

struct Story
{
  std::map<double, Scene> scenes;

  std::set<std::string> scalarProperties;
  std::set<std::string> vectorProperties;

  struct Metadata
  {
    QVector3D start;
    QVector3D end;
    double startTime;
    double endTime;
    float largestRadius;
    std::map<std::string, float> largestScalars;
    std::map<std::string, float> largestVectors;
  } metadata;

  QVector3D getOrigin() const;
  float getBaseScale() const;
};

#endif