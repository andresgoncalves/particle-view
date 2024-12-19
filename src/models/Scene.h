#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Particle.h"

class Scene
{
public:
  Scene();

  std::vector<Particle> particles;
};

#endif