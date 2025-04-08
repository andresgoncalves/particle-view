#ifndef CUSTOM_LOADER_H
#define CUSTOM_LOADER_H

#include <map>
#include <vector>
#include <string>

#include "StoryLoader.h"

class CustomLoader : public StoryLoader
{
public:
  enum DefaultProperty
  {
    X,
    Y,
    Z,
    R,
  };

  void setColumnCount(int count);
  void setDefaultProperty(DefaultProperty property, int column);
  void setCustomProperty(std::string property, int column);

  Story load(std::istream &input) override;

private:
  int columnCount = 0;
  std::map<DefaultProperty, int> defaultProperties;
  std::map<std::string, int> customProperties;

  Particle loadParticle(std::istream &input);
  Scene loadScene(std::istream &input, size_t particleCount);
};

#endif