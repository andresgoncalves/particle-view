#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Particle.h"

struct Scene
{
  Scene();

  std::vector<Particle> particles;
};

#endif