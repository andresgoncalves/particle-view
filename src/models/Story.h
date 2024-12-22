#ifndef STORY_H
#define STORY_H

#include <map>

#include "Scene.h"

struct Story
{
  Story();

  std::map<double, Scene> scenes;
};

#endif