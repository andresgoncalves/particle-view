#ifndef STORY_H
#define STORY_H

#include <map>
#include <string>
#include <vector>

#include "Scene.h"

struct Story
{
  Story();

  std::map<double, Scene> scenes;
  std::vector<std::string> customProperties;
};

#endif