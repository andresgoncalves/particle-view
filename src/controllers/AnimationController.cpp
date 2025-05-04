
#include "AnimationController.h"

#include "animation/StepAnimationStrategy.h"

AnimationController::AnimationController() : animationStrategy{std::make_unique<StepAnimationStrategy>()} {}

void AnimationController::play()
{
  startTime = playing ? startTime : std::chrono::steady_clock::now() - (pauseTime - startTime);
  playing = true;
  pauseTime = {};
  playingObservable.notify();
}

void AnimationController::pause()
{
  pauseTime = std::chrono::steady_clock::now();
  playing = false;
  playingObservable.notify();
}

void AnimationController::reset()
{
  startTime = pauseTime = std::chrono::steady_clock::now();
  updateTime();
}

void AnimationController::updateTime()
{
  auto now = playing ? std::chrono::steady_clock::now() : pauseTime;

  double duration = 1e-9 * (now - startTime).count();

  auto minTime = getFirstScene().time;
  auto maxTime = getLastScene().time;

  auto computedTime = minTime + duration * animationSpeed;

  time = std::clamp(computedTime, minTime, maxTime);

  if (computedTime > maxTime)
  {
    pause();
  }

  timeObservable.notify();
}

void AnimationController::skip(double delta)
{
  auto duration = std::chrono::nanoseconds(static_cast<long long>(1e9 * delta / animationSpeed));
  startTime -= duration;
  updateTime();
}

void AnimationController::setStory(const Story &story)
{
  this->story = story;
}

const Story &AnimationController::getStory() const
{
  return story;
}

void AnimationController::setTime(double time)
{
  startTime = std::chrono::steady_clock::now() - std::chrono::nanoseconds(static_cast<long long>(1e9 * time / animationSpeed));
  pauseTime = playing ? std::chrono::steady_clock::time_point{} : std::chrono::steady_clock::now();
  updateTime();
}

void AnimationController::setAnimationSpeed(double animationSpeed)
{
  this->animationSpeed = animationSpeed;
}

void AnimationController::setAnimationStrategy(std::unique_ptr<AnimationStrategy> animationStrategy)
{
  this->animationStrategy = std::move(animationStrategy);
}

double AnimationController::getAnimationSpeed() const
{
  return animationSpeed;
}

double AnimationController::getTime() const
{
  return time;
};

Scene AnimationController::getScene() const
{
  return getScene(getTime());
}

Scene AnimationController::getScene(double time) const
{
  return animationStrategy->getScene(story, time);
}

Scene AnimationController::getFirstScene() const
{
  if (story.scenes.empty())
    return Scene{};

  return story.scenes.begin()->second;
};

Scene AnimationController::getLastScene() const
{
  if (story.scenes.empty())
    return Scene{};

  return std::prev(story.scenes.end())->second;
};

double AnimationController::getDuration() const
{
  auto minTime = getFirstScene().time;
  auto maxTime = getLastScene().time;

  return maxTime - minTime;
}

bool AnimationController::isPlaying() const
{
  return playing;
}
