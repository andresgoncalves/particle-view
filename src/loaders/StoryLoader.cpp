#include "StoryLoader.h"

#include <algorithm>
#include <sstream>

void StoryLoader::load(std::istream &input)
{
  data.clear();

  while (!input.eof())
  {
    auto line = std::string{};
    std::getline(input, line);

    // Skip empty line
    if (line.empty())
      continue;

    auto rowStream = std::istringstream{line};
    auto row = std::vector<std::string>{};
    auto item = std::string{};
    // Get items
    while (rowStream >> item)
    {
      // Check quoted item
      if (item.starts_with('"'))
      {
        auto stream = std::ostringstream{item};
        // Append text until closing quote
        while (!stream.str().ends_with('"') && rowStream >> item)
          stream << item;
        // Get full item
        item = stream.str();
        // Remove quotes
        item.substr(1, item.length() - 2);
      }
      // Add parts to line
      row.push_back(item);
    }
    // Add lines
    data.push_back(row);
  }
}

void StoryLoader::setParticleProperties(PropertyDefinitionMap &particleProperties)
{
  this->particleProperties = particleProperties;
}

void StoryLoader::setSceneProperties(PropertyDefinitionMap &sceneProperties)
{
  this->sceneProperties = sceneProperties;
}

const StoryLoader::PropertyDefinitionMap &StoryLoader::getParticleProperties() const
{
  return particleProperties;
}

const StoryLoader::PropertyDefinitionMap &StoryLoader::getSceneProperties() const
{
  return sceneProperties;
}

int StoryLoader::getParticlePropertyCount() const
{
  return data.size() > 1 ? data[1].size() : 0;
}

int StoryLoader::getScenePropertyCount() const
{
  return data.size() > 0 ? data[0].size() : 0;
}

Story StoryLoader::parse()
{
  auto story = Story{};

  // Parse scenes
  int sceneId = 1;
  for (auto rowIterator = data.begin(); rowIterator != data.end(); rowIterator++)
  {
    auto scene = parseScene(rowIterator, sceneId++);
    story.scenes[scene.getTime()] = scene;
  }

  // Set story data
  story.metadata = getMetadata(story);

  return story;
}

Scene StoryLoader::parseScene(LoadedData::iterator &rowIterator, int sceneId)
{
  auto row = *rowIterator;

  auto scene = Scene{};

  // Get particle count
  scene.properties = parseRow(row, sceneProperties);

  // Parse particles
  int particleId = 0;
  for (; particleId < scene.getParticleCount(); particleId++)
  {
    rowIterator++;
    if (rowIterator == data.end())
    {
      // TODO: throw error: reached EOF
    }
    auto particle = parseParticle(*rowIterator, particleId);
    scene.particles.push_back(particle);
  }

  // Set scene data
  scene.frame = sceneId;
  scene.metadata = getMetadata(scene);

  return scene;
}

Particle StoryLoader::parseParticle(LoadedData::value_type &row, int particleId)
{
  auto particle = Particle{};
  particle.properties = parseRow(row, particleProperties);

  return particle;
}

PropertyMap StoryLoader::parseRow(LoadedData::value_type &row, PropertyDefinitionMap properties)
{
  PropertyMap propertyValues;

  for (auto [propertyName, definition] : properties)
  {
    switch (definition.first)
    {
    case PropertyType::Scalar:
    {
      auto index = std::get<IndexType>(definition.second);
      auto value = index >= 0 && index < row.size() ? std::stof(row[index]) : 0.0f;
      propertyValues.emplace(propertyName, ScalarProperty{value});
      break;
    }
    case PropertyType::Vector:
    {
      auto [xIndex, yIndex, zIndex] = std::get<IndicesType>(definition.second);
      auto xValue = xIndex >= 0 && xIndex < row.size() ? std::stof(row[xIndex]) : 0.0f;
      auto yValue = yIndex >= 0 && yIndex < row.size() ? std::stof(row[yIndex]) : 0.0f;
      auto zValue = zIndex >= 0 && zIndex < row.size() ? std::stof(row[zIndex]) : 0.0f;
      propertyValues.emplace(propertyName, VectorProperty{{xValue, yValue, zValue}});
      break;
    }
    case PropertyType::String:
    {
      auto index = std::get<IndexType>(definition.second);
      auto value = index >= 0 && index < row.size() ? row[index] : "";
      propertyValues.emplace(propertyName, StringProperty{value});
      break;
    }
    }
  }

  return propertyValues;
}

Scene::Metadata StoryLoader::getMetadata(const Scene &scene) const
{
  if (scene.particles.size() == 0)
    return Scene::Metadata{};

  auto particleProperties = PropertyTypeMap{};
  for (auto particle : scene.particles)
    for (auto [propertyName, property] : particle.properties)
      particleProperties.try_emplace(propertyName, property.getType());

  std::vector<Particle>::const_iterator start[] = {
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().x() - a.getRadius()) < (b.getPosition().x() - b.getRadius()); }),
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().y() - a.getRadius()) < (b.getPosition().y() - b.getRadius()); }),
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().z() - a.getRadius()) < (b.getPosition().z() - b.getRadius()); }),
  };

  std::vector<Particle>::const_iterator end[] = {
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().x() + a.getRadius()) < (b.getPosition().x() + b.getRadius()); }),
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().y() + a.getRadius()) < (b.getPosition().y() + b.getRadius()); }),
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.getPosition().z() + a.getRadius()) < (b.getPosition().z() + b.getRadius()); }),
  };

  auto maxValues = std::map<std::string, float>{};
  for (auto [propertyName, propertyType] : particleProperties)
  {
    switch (propertyType)
    {
    case PropertyType::Scalar:
    {
      auto compareScalar = [=](const Particle &a, const Particle &b)
      {
        auto aValue = a.getProperty(propertyName);
        auto bValue = b.getProperty(propertyName);

        if (!aValue.has_value())
          return true;
        if (!bValue.has_value())
          return false;

        return aValue.value().getValue<PropertyType::Scalar>() < bValue.value().getValue<PropertyType::Scalar>();
      };

      auto maxValue = std::max_element(scene.particles.begin(), scene.particles.end(), compareScalar);
      maxValues[propertyName] = maxValue->getProperty(propertyName)->getValue<PropertyType::Scalar>()->value;
      break;
    }
    case PropertyType::Vector:
    {
      auto compareVector = [=](const Particle &a, const Particle &b)
      {
        auto aValue = a.getProperty(propertyName);
        auto bValue = b.getProperty(propertyName);

        if (!aValue.has_value())
          return true;
        if (!bValue.has_value())
          return false;

        return aValue.value().getValue<PropertyType::Vector>()->value.length() < bValue.value().getValue<PropertyType::Vector>()->value.length();
      };

      auto maxValue = std::max_element(scene.particles.begin(), scene.particles.end(), compareVector);
      maxValues[propertyName] = maxValue->getProperty(propertyName)->getValue<PropertyType::Vector>()->value.length();
      break;
    }
    case PropertyType::String:
      break;
    }
  }

  auto metadata = Scene::Metadata{
      .start = {
          start[0]->getPosition().x() - start[0]->getRadius(),
          start[1]->getPosition().y() - start[1]->getRadius(),
          start[2]->getPosition().z() - start[2]->getRadius(),
      },
      .end = {
          end[0]->getPosition().x() + end[0]->getRadius(),
          end[1]->getPosition().y() + end[1]->getRadius(),
          end[2]->getPosition().z() + end[2]->getRadius(),
      },
      .maxValues = maxValues,
      .particleProperties = particleProperties};

  return metadata;
}

Story::Metadata StoryLoader::getMetadata(const Story &story) const
{
  if (story.scenes.size() == 0)
    return Story::Metadata{};

  auto particleProperties = PropertyTypeMap{};
  auto sceneProperties = PropertyTypeMap{};
  for (auto [_, scene] : story.scenes)
  {
    for (auto [propertyName, propertyType] : scene.metadata.particleProperties)
      particleProperties.try_emplace(propertyName, propertyType);
    for (auto [propertyName, property] : scene.properties)
      sceneProperties.try_emplace(propertyName, property.getType());
  }

  std::map<double, Scene>::const_iterator start[] = {
      std::min_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.start.x() < b.second.metadata.start.x(); }),
      std::min_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.start.y() < b.second.metadata.start.y(); }),
      std::min_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.start.z() < b.second.metadata.start.z(); }),
  };

  std::map<double, Scene>::const_iterator end[] = {
      std::max_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.end.x() < b.second.metadata.end.x(); }),
      std::max_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.end.y() < b.second.metadata.end.y(); }),
      std::max_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                       { return a.second.metadata.end.z() < b.second.metadata.end.z(); }),
  };

  auto maxValues = std::map<std::string, float>{};
  for (auto [propertyName, propertyType] : particleProperties)
  {
    if (propertyType == PropertyType::String)
      continue;

    auto compare = [=](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
    {
      auto aScalar = a.second.metadata.maxValues.find(propertyName);
      auto bScalar = b.second.metadata.maxValues.find(propertyName);

      if (aScalar == a.second.metadata.maxValues.end())
        return true;
      if (bScalar == b.second.metadata.maxValues.end())
        return false;

      return aScalar->second < bScalar->second;
    };
    auto maxValue = std::max_element(story.scenes.begin(), story.scenes.end(), compare);
    maxValues[propertyName] = maxValue->second.metadata.maxValues.at(propertyName);
  }

  auto metadata = Story::Metadata{
      .start = {
          start[0]->second.metadata.start.x(),
          start[1]->second.metadata.start.y(),
          start[2]->second.metadata.start.z(),
      },
      .end = {
          end[0]->second.metadata.end.x(),
          end[1]->second.metadata.end.y(),
          end[2]->second.metadata.end.z(),
      },
      .startTime = story.scenes.begin()->first,
      .endTime = std::prev(story.scenes.end())->first,
      .maxValues = maxValues,
      .particleProperties = particleProperties,
      .sceneProperties = sceneProperties};

  return metadata;
}
