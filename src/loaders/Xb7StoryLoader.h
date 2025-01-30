#ifndef XB7_STORY_LOADER_H
#define XB7_STORY_LOADER_H

#include "StoryLoader.h"

class Xb7StoryLoader : public StoryLoader
{
public:
  Xb7StoryLoader();

  Story load(std::istream &input);

  static Xb7StoryLoader &getInstance();

private:
  static Xb7StoryLoader instance;

  Particle loadParticle(std::istream &input);
  Scene loadScene(std::istream &input, size_t particleCount);
};

#endif