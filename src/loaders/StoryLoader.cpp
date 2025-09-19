#include "StoryLoader.h"

#include <algorithm>
#include <sstream>

Story StoryLoader::load(std::istream &input)
{
  auto story = Story{};

  for (int frame = 1; !input.eof(); frame++)
  {
    size_t count;
    float time;

    std::string line;
    std::getline(input, line);
    auto lineStream = std::istringstream{line};

    lineStream >> count >> time;

    auto scene = loadScene(input, count);

    scene.frame = frame;
    scene.time = time;
    scene.metadata = getMetadata(scene);

    for (auto property : scene.particleProperties)
      story.particleProperties.insert(property);

    story.scenes[time] = scene;
  }

  story.metadata = getMetadata(story);

  return story;
}

Scene StoryLoader::loadScene(std::istream &input, size_t particleCount)
{
  auto scene = Scene{};

  while (particleCount-- && !input.eof())
  {
    std::string line;
    std::getline(input, line);
    auto lineStream = std::istringstream{line, std::ios::in};

    auto particle = loadParticle(lineStream);
    scene.particles.push_back(particle);

    for (auto [propertyName, property] : particle.properties)
      scene.particleProperties.insert({propertyName, property.getType()});
  }

  return scene;
}

Particle StoryLoader::loadParticle(std::istream &input)
{
  std::vector<std::string> rawValues;
  std::string rawValue;

  while (input >> rawValue)
    rawValues.push_back(rawValue);

  auto particle = Particle{};

  for (auto [propertyName, definition] : properties)
  {
    switch (definition.first)
    {
    case PropertyType::Scalar:
    {
      auto index = std::get<IndexType>(definition.second);
      auto value = std::stof(rawValues[index]);
      particle.setProperty(propertyName, ScalarProperty{value});
      break;
    }
    case PropertyType::Vector:
    {
      auto [xIndex, yIndex, zIndex] = std::get<IndicesType>(definition.second);
      particle.setProperty(propertyName, VectorProperty{{
                                             std::stof(rawValues[xIndex]),
                                             std::stof(rawValues[yIndex]),
                                             std::stof(rawValues[zIndex]),
                                         }});
      break;
    }
    case PropertyType::String:
    {
      auto index = std::get<IndexType>(definition.second);
      auto value = rawValues[index];
      particle.setProperty(propertyName, StringProperty{value});
      break;
    }
    }
  }

  return particle;
}

Scene::Metadata StoryLoader::getMetadata(const Scene &scene) const
{
  if (scene.particles.size() == 0)
    return Scene::Metadata{};

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
  for (auto [propertyName, propertyType] : scene.particleProperties)
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
      .maxValues = maxValues};

  return metadata;
}

Story::Metadata StoryLoader::getMetadata(const Story &story) const
{
  if (story.scenes.size() == 0)
    return Story::Metadata{};

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
  for (auto [propertyName, PropertyType] : story.particleProperties)
  {
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
      .maxValues = maxValues};

  return metadata;
}
