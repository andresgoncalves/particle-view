#include <QtGui/QKeyEvent>

#include "KeyEventFilter.h"

bool KeyEventFilter::isKeyPressed(int key) const
{
  return pressedKeys.contains(key);
}

void KeyEventFilter::addListener(int key, const KeyListener &listener, KeyListenerType type)
{
  switch (type)
  {
  case Single:
    return addListener(key, listener, keyListeners.single);
  case Multi:
    return addListener(key, listener, keyListeners.multi);
  }
}

void KeyEventFilter::removeListener(int key, const KeyListener &listener, KeyListenerType type)
{
  switch (type)
  {
  case Single:
    return removeListener(key, listener, keyListeners.single);
  case Multi:
    return removeListener(key, listener, keyListeners.multi);
  }
}

void KeyEventFilter::addListener(int key, const KeyListener &listener, KeyListenerMap &listeners)
{
  listeners.insert(std::make_pair(key, listener));
}

void KeyEventFilter::removeListener(int key, const KeyListener &listener, KeyListenerMap &listeners)
{
  if (listener == nullptr)
  {
    listeners.erase(key);
  }
  else
  {
    auto [begin, end] = listeners.equal_range(key);
    for (auto it = begin; it != end;)
    {
      if (listener.target<void()>() == it->second.target<void()>())
        it = listeners.erase(it);
      else
        it++;
    }
  }
}

void KeyEventFilter::notifyListeners(int key, KeyListenerMap &listeners)
{
  auto [begin, end] = listeners.equal_range(key);
  for (auto it = begin; it != end; it++)
    it->second();
}

bool KeyEventFilter::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::KeyPress)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    bool isNew = pressedKeys.insert(keyEvent->key()).second;

    if (isNew)
      notifyListeners(keyEvent->key(), keyListeners.single);

    notifyListeners(keyEvent->key(), keyListeners.multi);
  }
  else if (event->type() == QEvent::KeyRelease)
  {
    auto keyEvent = static_cast<QKeyEvent *>(event);
    pressedKeys.erase(keyEvent->key());
  }
  return QObject::eventFilter(obj, event);
};