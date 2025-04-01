
#include "StoryController.h"

StoryController::StoryController() {}

void StoryController::play()
{
  startTime = playing ? startTime : std::chrono::steady_clock::now() - (pauseTime - startTime);
  playing = true;
  pauseTime = {};
  playingObservable.notify();
}

void StoryController::pause()
{
  pauseTime = std::chrono::steady_clock::now();
  playing = false;
  playingObservable.notify();
}

void StoryController::reset()
{
  startTime = pauseTime = std::chrono::steady_clock::now();
  updateTime();
}

void StoryController::updateTime()
{
  auto now = playing ? std::chrono::steady_clock::now() : pauseTime;

  double duration = 1e-9 * (now - startTime).count();

  auto [minTime, _] = getFirstScene();
  auto [maxTime, __] = getLastScene();

  auto computedTime = duration * timeScale;

  time = std::clamp(computedTime, minTime, maxTime);

  if (computedTime > maxTime)
  {
    pause();
  }

  timeObservable.notify();
}

void StoryController::skip(double delta)
{
  auto duration = std::chrono::nanoseconds(static_cast<long long>(1e9 * delta / timeScale));
  startTime -= duration;
  updateTime();
}

void StoryController::setStory(const Story &story)
{
  this->story = story;
}

Story &StoryController::getStory()
{
  return story;
}

void StoryController::setTime(double time)
{
  startTime = std::chrono::steady_clock::now() - std::chrono::nanoseconds(static_cast<long long>(1e9 * time / timeScale));
  pauseTime = playing ? std::chrono::steady_clock::time_point{} : std::chrono::steady_clock::now();
  updateTime();
}

double StoryController::getTime() const
{
  return time;
};

std::pair<double, Scene> StoryController::getScene() const
{
  return getScene(getTime());
}

std::pair<double, Scene> StoryController::getScene(double time) const
{
  if (story.scenes.empty())
    return std::make_pair(std::numeric_limits<double>::min(), Scene{});

  auto next = story.scenes.lower_bound(time);

  if (next == story.scenes.begin())
    return *next;

  auto prev = std::prev(next);

  if (next == story.scenes.end())
    return *prev;

  if (next->first == time)
    return *next;

  return std::make_pair(time, interpolateScene(time, *prev, *next));
}

std::pair<double, Scene> StoryController::getFirstScene() const
{
  if (story.scenes.empty())
    return std::make_pair(std::numeric_limits<double>::min(), Scene{});

  return *story.scenes.begin();
};

std::pair<double, Scene> StoryController::getLastScene() const
{
  if (story.scenes.empty())
    return std::make_pair(std::numeric_limits<double>::min(), Scene{});

  return *std::prev(story.scenes.end());
};

double StoryController::getDuration() const
{
  double minTime = getFirstScene().first;
  double maxTime = getLastScene().first;

  return maxTime - minTime;
};

Scene StoryController::interpolateScene(double time, const std::pair<double, Scene> &prev, const std::pair<double, Scene> &next) const
{
  double ratio = (time - prev.first) / (next.first - prev.first);

  auto scene = Scene{};

  for (
      auto prevIt = prev.second.particles.begin(), nextIt = next.second.particles.begin();
      prevIt != prev.second.particles.end() && nextIt != next.second.particles.end();
      ++prevIt, ++nextIt)
  {
    auto particle = *prevIt;
    particle.position = prevIt->position + (nextIt->position - prevIt->position) * ratio;
    scene.particles.push_back(particle);
  }

  return scene;
}

bool StoryController::isPlaying() const
{
  return playing;
}
