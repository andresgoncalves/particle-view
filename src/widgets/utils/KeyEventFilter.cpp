#include <QtGui/QKeyEvent>

#include "KeyEventFilter.h"

bool KeyEventFilter::isKeyPressed(int key) const
{
  return pressedKeys.contains(key);
}

void KeyEventFilter::addListener(int key, const std::function<void()> listener)
{
  keyListeners.insert(std::make_pair(key, listener));
}

void KeyEventFilter::removeListener(int key, const std::function<void()> listener)
{
  if (listener == nullptr)
  {
    keyListeners.erase(key);
  }
  else
  {
    auto [begin, end] = keyListeners.equal_range(key);
    for (auto it = begin; it != end;)
    {
      if (listener.target<void()>() == it->second.target<void()>())
        it = keyListeners.erase(it);
      else
        it++;
    }
  }
}

bool KeyEventFilter::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::KeyPress)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    bool isNew = pressedKeys.insert(keyEvent->key()).second;
    if (isNew)
    {
      auto [begin, end] = keyListeners.equal_range(keyEvent->key());
      for (auto it = begin; it != end; it++)
        it->second();
    }
  }
  else if (event->type() == QEvent::KeyRelease)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    pressedKeys.erase(keyEvent->key());
  }
  return QObject::eventFilter(obj, event);
};