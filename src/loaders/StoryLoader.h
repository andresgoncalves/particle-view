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
  std::map<std::string, int> scalarProperties;
  std::map<std::string, int[3]> vectorProperties;

private:
  Particle loadParticle(std::istream &input);
  Scene loadScene(std::istream &input, size_t particleCount);

  Scene::Metadata getMetadata(const Scene &scene) const;
  Story::Metadata getMetadata(const Story &story) const;
};

#endif