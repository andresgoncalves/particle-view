
#include "StoryController.h"

StoryController::StoryController() {}

void StoryController::play()
{
  startTime = playing ? pauseTime : std::chrono::steady_clock::now();
  playing = true;
  pauseTime = {};
}

void StoryController::pause()
{
  pauseTime = std::chrono::steady_clock::now();
  playing = false;
}

void StoryController::reset()
{
  startTime = pauseTime = std::chrono::steady_clock::now();
}

void StoryController::skip(double delta)
{
  auto duration = std::chrono::nanoseconds(static_cast<long long>(1e9 * delta / timeScale));
  startTime -= duration;
}

Scene StoryController::getScene() const
{
  auto currentTime = playing ? std::chrono::steady_clock::now() : pauseTime;

  double duration = 1e-9 * (currentTime - startTime).count();

  double time = duration * timeScale;

  return getScene(time);
}

Scene StoryController::getScene(double time) const
{
  if (story.scenes.empty())
    return Scene{};

  auto next = story.scenes.lower_bound(time);

  if (next == story.scenes.begin())
    return next->second;

  auto prev = std::prev(next);

  if (next == story.scenes.end())
    return prev->second;

  if (next->first == time)
    return next->second;

  return interpolateScene(time, *prev, *next);
}

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