#ifndef STORY_CONTROLLER_H
#define STORY_CONTROLLER_H

#include <chrono>

#include "../models/Story.h"

class StoryController
{
public:
  StoryController();

  void play();
  void pause();
  void skip(double delta);

  Scene getScene() const;
  Scene getScene(double time) const;

  bool isPlaying() const;

  Story story;

private:
  bool playing = false;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point pauseTime;

  double timeScale = 1.0;
};

#endif