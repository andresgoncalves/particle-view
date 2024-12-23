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
  void reset();
  void skip(double delta);

  void setTime(double time);

  double getTime() const;
  double getDuration() const;

  std::pair<double, Scene> getScene() const;
  std::pair<double, Scene> getScene(double time) const;

  std::pair<double, Scene> getFirstScene() const;
  std::pair<double, Scene> getLastScene() const;

  bool isPlaying() const;

  Story story;

private:
  Scene interpolateScene(double time, const std::pair<double, Scene> &prev, const std::pair<double, Scene> &next) const;

  bool playing = false;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point pauseTime;

  double timeScale = 1.0;
};

#endif