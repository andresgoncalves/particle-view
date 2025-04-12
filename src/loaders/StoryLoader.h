#ifndef STORY_LOADER_H
#define STORY_LOADER_H

#include <map>
#include <vector>
#include <string>
#include <istream>

#include "../models/Story.h"

class StoryLoader
{
public:
  enum DefaultProperty
  {
    X,
    Y,
    Z,
    VX,
    VY,
    VZ,
    R,
  };

  Story load(std::istream &input);

  std::map<DefaultProperty, int> defaultProperties;
  std::map<std::string, int> customProperties;

private:
  Particle loadParticle(std::istream &input);
  Scene loadScene(std::istream &input, size_t particleCount);
};

#endif