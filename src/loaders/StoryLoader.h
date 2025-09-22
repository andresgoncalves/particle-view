#ifndef STORY_LOADER_H
#define STORY_LOADER_H

#include <map>
#include <vector>
#include <string>
#include <istream>
#include <array>

#include <models/Story.h>

class StoryLoader
{
public:
  using IndexType = unsigned int;
  using IndicesType = std::array<IndexType, 3>;
  using PropertyDefinition = std::pair<PropertyType, std::variant<IndexType, IndicesType>>;
  using PropertyDefinitionMap = std::map<std::string, PropertyDefinition>;

  /** Load file */
  void load(std::istream &input);

  /** Get particle properties */
  void setParticleProperties(PropertyDefinitionMap &particleProperties);
  /** Set scene properties */
  void setSceneProperties(PropertyDefinitionMap &sceneProperties);

  /** Get particle properties */
  const PropertyDefinitionMap &getParticleProperties() const;
  /** Set scene properties */
  const PropertyDefinitionMap &getSceneProperties() const;

  /** Get particle property count */
  int getParticlePropertyCount() const;
  /** Set scene property count */
  int getScenePropertyCount() const;

  /** Parse loaded file */
  Story parse();

private:
  using LoadedData = std::vector<std::vector<std::string>>;

  /** Current loaded data */
  LoadedData data;

  /** Particle property definitions */
  PropertyDefinitionMap particleProperties;
  /** Scene property definitions */
  PropertyDefinitionMap sceneProperties;

  /** Parse one scene */
  Scene parseScene(LoadedData::iterator &rowIterator, int sceneId);
  /** Parse one particle */
  Particle parseParticle(LoadedData::value_type &row, int particleId);

  /** Parse one row */
  PropertyMap parseRow(LoadedData::value_type &row, PropertyDefinitionMap properties);

  Scene::Metadata getMetadata(const Scene &scene) const;
  Story::Metadata getMetadata(const Story &story) const;
};

#endif