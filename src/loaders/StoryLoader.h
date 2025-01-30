#ifndef STORY_LOADER_H
#define STORY_LOADER_H

#include <istream>

#include "../models/Story.h"

class StoryLoader
{
public:
  virtual ~StoryLoader() = default;

  virtual Story load(std::istream &input) = 0;
};

#endif