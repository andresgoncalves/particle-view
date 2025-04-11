#include "StoryLoader.h"

#include <sstream>

void StoryLoader::setColumnCount(int count)
{
  this->columnCount = count;

  for (auto property : defaultProperties)
  {
    if (property.second >= count)
      property.second = -1;
  }
}

void StoryLoader::setDefaultProperty(DefaultProperty property, int column)
{
  defaultProperties[property] = column;
}

void StoryLoader::setCustomProperty(std::string property, int column)
{
  customProperties[property] = column;
}

Story StoryLoader::load(std::istream &input)
{
  auto story = Story{};
  for (auto [key, _] : customProperties)
    story.customProperties.push_back(key);

  while (!input.eof())
  {
    size_t count;
    float time, xStart, yStart, zStart, xEnd, yEnd, zEnd;

    std::string line;
    std::getline(input, line);
    auto lineStream = std::istringstream{line};

    lineStream >> count >> time >> xStart >> yStart >> zStart >> xEnd >> yEnd >> zEnd;

    auto scene = loadScene(input, count);

    scene.time = time;
    scene.geometryStart = {xStart, zStart, yStart};
    scene.geometryEnd = {xEnd, zEnd, yEnd};

    story.scenes[time] = scene;
  }

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
  }

  return scene;
}

Particle StoryLoader::loadParticle(std::istream &input)
{
  std::vector<float> columnValues;
  float value;

  while (input >> value)
  {
    columnValues.push_back(value);
  }

  auto defaultValues = std::map<DefaultProperty, float>{};
  auto customValues = std::map<std::string, float>{};

  for (auto property : defaultProperties)
  {
    if (property.second >= 0 && property.second < columnValues.size())
      defaultValues[property.first] = columnValues[property.second];
  }
  for (auto property : customProperties)
  {
    if (property.second >= 0 && property.second < columnValues.size())
      customValues[property.first] = columnValues[property.second];
  }

  auto getDefaultValue = [&](DefaultProperty property, float fallback)
  {
    auto it = defaultValues.find(property);
    return it != defaultValues.end() ? it->second : fallback;
  };

  auto particle = Particle{
      .radius = getDefaultValue(DefaultProperty::R, 1.0f),
      .position = {
          getDefaultValue(DefaultProperty::X, 0.0f),
          getDefaultValue(DefaultProperty::Y, 0.0f),
          getDefaultValue(DefaultProperty::Z, 0.0f),
      },
      .velocity = {
          getDefaultValue(DefaultProperty::VX, 0.0f),
          getDefaultValue(DefaultProperty::VY, 0.0f),
          getDefaultValue(DefaultProperty::VZ, 0.0f),
      },
      .customProperties = customValues,
  };

  return particle;
}
