
#include "StoryController.h"

StoryController::StoryController() {}

void StoryController::play()
{
  playing = true;
  startTime = std::chrono::steady_clock::now();
}

void StoryController::pause()
{
  playing = false;
  pauseTime = std::chrono::steady_clock::now();
}

void StoryController::skip(double delta)
{
  startTime -= std::chrono::seconds(static_cast<long long>(delta / timeScale));
}

Scene StoryController::getScene() const
{
  auto currentTime = playing ? std::chrono::steady_clock::now() : pauseTime;

  double duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

  double time = duration * timeScale;

  return getScene(time);
}

Scene StoryController::getScene(double time) const
{
  if (story.scenes.empty())
    return Scene{};

  auto lower = story.scenes.lower_bound(time);

  if (lower == story.scenes.begin())
    return lower->second;

  auto prev = std::prev(lower);

  if (lower == story.scenes.end())
    return prev->second;

  if (time - prev->first <= lower->first - time)
    return prev->second;

  return lower->second;
}

bool StoryController::isPlaying() const
{
  return playing;
}