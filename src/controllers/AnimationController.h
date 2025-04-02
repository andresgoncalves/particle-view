#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <chrono>

#include "Observable.h"
#include "animation/AnimationStrategy.h"
#include "../models/Story.h"

class AnimationController
{
public:
  AnimationController();

  void play();
  void pause();
  void reset();
  void skip(double delta);
  void updateTime();

  void setTime(double time);
  void setAnimationSpeed(double animationSpeed);

  void setStory(const Story &story);

  Story &getStory();

  double getTime() const;
  double getDuration() const;
  double getAnimationSpeed() const;

  Scene getScene() const;
  Scene getScene(double time) const;

  Scene getFirstScene() const;
  Scene getLastScene() const;

  bool isPlaying() const;

  Observable<double> timeObservable = time;
  Observable<bool> playingObservable = playing;
  Observable<double> animationSpeedObservable = animationSpeed;

private:
  Story story;

  bool playing = false;
  double time = 0.0;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point pauseTime;

  std::unique_ptr<AnimationStrategy> animationStrategy;

  double animationSpeed = 1.0;
};

#endif