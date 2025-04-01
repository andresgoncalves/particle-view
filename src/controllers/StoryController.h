#ifndef STORY_CONTROLLER_H
#define STORY_CONTROLLER_H

#include <chrono>

#include "Observable.h"
#include "../models/Story.h"

class StoryController
{
public:
  StoryController();

  void play();
  void pause();
  void reset();
  void skip(double delta);
  void updateTime();

  void setTime(double time);

  void setStory(const Story &story);

  Story &getStory();

  double getTime() const;
  double getDuration() const;

  std::pair<double, Scene> getScene() const;
  std::pair<double, Scene> getScene(double time) const;

  std::pair<double, Scene> getFirstScene() const;
  std::pair<double, Scene> getLastScene() const;

  bool isPlaying() const;

  Observable<double> timeObservable = time;
  Observable<bool> playingObservable = playing;

private:
  Story story;

  Scene interpolateScene(double time, const std::pair<double, Scene> &prev, const std::pair<double, Scene> &next) const;

  bool playing = false;
  double time = 0.0;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point pauseTime;

  double timeScale = 1.0;
};

#endif