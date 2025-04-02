#include <sstream>

#include "Xb7StoryLoader.h"

Xb7StoryLoader::Xb7StoryLoader() {}

Story Xb7StoryLoader::load(std::istream &input)
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

    time *= 1e-2;
    auto scene = loadScene(input, count);

    scene.time = time;
    scene.geometryStart = {xStart, zStart, yStart};
    scene.geometryEnd = {xEnd, zEnd, yEnd};

    scene.geometryStart *= 0.1;
    scene.geometryEnd *= 0.1;

    story.scenes.insert(std::make_pair(time, scene));
  }

  return story;
}

Scene Xb7StoryLoader::loadScene(std::istream &input, size_t particleCount)
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

Particle Xb7StoryLoader::loadParticle(std::istream &input)
{
  auto particle = Particle{};

  float x, y, z, vx, vy, vz, radius;
  int info;
  input >> x >> y >> z >> vx >> vy >> vz >> radius >> info;

  particle.position = {x, z, y};
  particle.position *= 0.1;
  switch (info)
  {
  case 1:
    particle.color = QVector3D{1.0f, 0.0f, 0.0f};
    break;
  case 2:
    particle.color = QVector3D{0.0f, 1.0f, 0.0f};
    break;
  case 3:
    particle.color = QVector3D{0.0f, 0.0f, 1.0f};
    break;
  default:
    particle.color = QVector3D{1.0f, 1.0f, 1.0f};
  }
  particle.radius = radius / 10;

  return particle;
}

Xb7StoryLoader &Xb7StoryLoader::getInstance()
{
  return instance;
}

Xb7StoryLoader Xb7StoryLoader::instance = {};