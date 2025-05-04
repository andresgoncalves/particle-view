#include "StoryLoader.h"

#include <algorithm>
#include <sstream>

Story StoryLoader::load(std::istream &input)
{
  auto story = Story{};
  for (auto [key, _] : scalarProperties)
    story.scalarProperties.push_back(key);
  for (auto [key, _] : vectorProperties)
    story.vectorProperties.push_back(key);

  while (!input.eof())
  {
    size_t count;
    float time;

    std::string line;
    std::getline(input, line);
    auto lineStream = std::istringstream{line};

    lineStream >> count >> time;

    auto scene = loadScene(input, count);

    scene.time = time;
    scene.metadata = getMetadata(scene);

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
  }

  return scene;
}

Particle StoryLoader::loadParticle(std::istream &input)
{
  std::vector<float> columnValues;
  float value;

  while (input >> value)
    columnValues.push_back(value);

  auto defaultValues = std::map<DefaultProperty, float>{};
  auto scalarValues = std::map<std::string, float>{};
  auto vectorValues = std::map<std::string, QVector3D>{};

  for (auto property : defaultProperties)
  {
    if (property.second >= 0 && property.second < columnValues.size())
      defaultValues[property.first] = columnValues[property.second];
  }
  for (auto property : scalarProperties)
  {
    if (property.second >= 0 && property.second < columnValues.size())
      scalarValues[property.first] = columnValues[property.second];
  }
  for (auto property : vectorProperties)
  {
    for (int i = 0; i < 3; i++)
    {
      if (property.second[i] >= 0 && property.second[i] < columnValues.size())
        vectorValues[property.first][i] = columnValues[property.second[i]];
    }
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
      .scalarProperties = scalarValues,
      .vectorProperties = vectorValues,
  };

  return particle;
}

Scene::Metadata StoryLoader::getMetadata(const Scene &scene) const
{
  if (scene.particles.size() == 0)
    return Scene::Metadata{};

  std::vector<Particle>::const_iterator start[] = {
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.x() - a.radius) < (b.position.x() - b.radius); }),
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.y() - a.radius) < (b.position.y() - b.radius); }),
      std::min_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.z() - a.radius) < (b.position.z() - b.radius); }),
  };

  std::vector<Particle>::const_iterator end[] = {
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.x() + a.radius) < (b.position.x() + b.radius); }),
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.y() + a.radius) < (b.position.y() + b.radius); }),
      std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                       { return (a.position.z() + a.radius) < (b.position.z() + b.radius); }),
  };

  std::vector<Particle>::const_iterator maxRadius = std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                                                                     { return a.radius < b.radius; });

  std::vector<Particle>::const_iterator maxVelocity = std::max_element(scene.particles.begin(), scene.particles.end(), [](const Particle &a, const Particle &b)
                                                                       { return a.velocity.length() < b.velocity.length(); });

  auto metadata = Scene::Metadata{
      .start = {
          start[0]->position.x() - start[0]->radius,
          start[1]->position.y() - start[1]->radius,
          start[2]->position.z() - start[2]->radius,
      },
      .end = {
          end[0]->position.x() + end[0]->radius,
          end[1]->position.y() + end[1]->radius,
          end[2]->position.z() + end[2]->radius,
      },
      .maxRadius = maxRadius->radius,
      .maxVelocity = maxVelocity->velocity.length()};

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

  std::map<double, Scene>::const_iterator maxRadius = std::max_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                                                                       { return a.second.metadata.maxRadius < b.second.metadata.maxRadius; });

  std::map<double, Scene>::const_iterator maxVelocity = std::max_element(story.scenes.begin(), story.scenes.end(), [](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
                                                                         { return a.second.metadata.maxVelocity < b.second.metadata.maxVelocity; });

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
      .maxRadius = maxRadius->second.metadata.maxRadius,
      .maxVelocity = maxVelocity->second.metadata.maxVelocity};

  return metadata;
}
