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

  auto largestScalars = std::map<std::string, float>{};
  for (auto [key, _] : scene.particles[0].scalarProperties)
  {
    auto compare = [=](const Particle &a, const Particle &b)
    {
      auto aScalar = a.scalarProperties.find(key);
      auto bScalar = b.scalarProperties.find(key);

      if (aScalar == a.scalarProperties.end())
        return true;
      if (bScalar == b.scalarProperties.end())
        return false;

      return aScalar->second < bScalar->second;
    };
    auto largest = std::max_element(scene.particles.begin(), scene.particles.end(), compare);
    largestScalars[key] = largest->scalarProperties.at(key);
  }

  auto largestVectors = std::map<std::string, float>{};
  for (auto [key, _] : scene.particles[0].vectorProperties)
  {
    auto compare = [=](const Particle &a, const Particle &b)
    {
      auto aVector = a.vectorProperties.find(key);
      auto bVector = b.vectorProperties.find(key);

      if (aVector == a.vectorProperties.end())
        return true;
      if (bVector == b.vectorProperties.end())
        return false;

      return aVector->second.length() < bVector->second.length();
    };
    auto largest = std::max_element(scene.particles.begin(), scene.particles.end(), compare);
    largestVectors[key] = largest->vectorProperties.at(key).length();
  }

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
      .maxVelocity = maxVelocity->velocity.length(),
      .largestScalars = largestScalars,
      .largestVectors = largestVectors,
  };

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

  auto largestScalars = std::map<std::string, float>{};
  for (auto [key, _] : story.scenes.begin()->second.metadata.largestScalars)
  {
    auto compare = [=](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
    {
      auto aScalar = a.second.metadata.largestScalars.find(key);
      auto bScalar = b.second.metadata.largestScalars.find(key);

      if (aScalar == a.second.metadata.largestScalars.end())
        return true;
      if (bScalar == b.second.metadata.largestScalars.end())
        return false;

      return aScalar->second < bScalar->second;
    };
    auto largest = std::max_element(story.scenes.begin(), story.scenes.end(), compare);
    largestScalars[key] = largest->second.metadata.largestScalars.at(key);
  }

  auto largestVectors = std::map<std::string, float>{};
  for (auto [key, _] : story.scenes.begin()->second.metadata.largestVectors)
  {
    auto compare = [=](const std::pair<double, Scene> &a, const std::pair<double, Scene> &b)
    {
      auto aVector = a.second.metadata.largestVectors.find(key);
      auto bVector = b.second.metadata.largestVectors.find(key);

      if (aVector == a.second.metadata.largestVectors.end())
        return true;
      if (bVector == b.second.metadata.largestVectors.end())
        return false;

      return aVector->second < bVector->second;
    };
    auto largest = std::max_element(story.scenes.begin(), story.scenes.end(), compare);
    largestVectors[key] = largest->second.metadata.largestVectors.at(key);
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
      .maxRadius = maxRadius->second.metadata.maxRadius,
      .maxVelocity = maxVelocity->second.metadata.maxVelocity,
      .largestScalars = largestScalars,
      .largestVectors = largestVectors,
  };

  return metadata;
}
