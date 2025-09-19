#ifndef STORY_LOADER_H
#define STORY_LOADER_H

#include <map>
#include <vector>
#include <string>
#include <istream>
#include <array>

#include "../models/Story.h"

class StoryLoader
{
public:
  using IndexType = unsigned int;
  using IndicesType = std::array<IndexType, 3>;
  using PropertyDefinition = std::pair<PropertyType, std::variant<IndexType, IndicesType>>;

  Story load(std::istream &input);

  std::map<std::string, PropertyDefinition> properties;

private:
  Particle loadParticle(std::istream &input);
  Scene loadScene(std::istream &input, size_t particleCount);

  Scene::Metadata getMetadata(const Scene &scene) const;
  Story::Metadata getMetadata(const Story &story) const;
};

#endif