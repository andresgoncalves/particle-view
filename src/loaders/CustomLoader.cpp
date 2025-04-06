#include "CustomLoader.h"

#include <sstream>

void CustomLoader::setColumnCount(int count)
{
  this->columnCount = count;

  for (auto property : defaultProperties)
  {
    if (property.second >= count)
      property.second = -1;
  }
}

void CustomLoader::setDefaultProperty(DefaultProperty property, int column)
{
  defaultProperties[property] = column;
}

// void CustomLoader::setCustomProperty(std::string property, int column)
// {
//   customProperties[property] = column;
// }

Story CustomLoader::load(std::istream &input)
{
  auto story = Story{};

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

Scene CustomLoader::loadScene(std::istream &input, size_t particleCount)
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

Particle CustomLoader::loadParticle(std::istream &input)
{
  std::vector<float> columnValues;
  float value;

  while (input >> value)
  {
    columnValues.push_back(value);
  }

  auto defaultValues = std::map<DefaultProperty, float>{};

  for (auto property : defaultProperties)
  {
    if (property.second >= 0 && property.second < columnValues.size())
      defaultValues[property.first] = columnValues[property.second];
  }

  auto x = defaultValues.find(DefaultProperty::X);
  auto y = defaultValues.find(DefaultProperty::Y);
  auto z = defaultValues.find(DefaultProperty::Z);
  auto r = defaultValues.find(DefaultProperty::R);

  auto particle = Particle{
      .radius = r != defaultValues.end() ? r->second : 1,
      .position = {
          x != defaultValues.end() ? x->second : 0,
          y != defaultValues.end() ? y->second : 0,
          z != defaultValues.end() ? z->second : 0,
      },
  };

  return particle;
}
