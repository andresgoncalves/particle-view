#ifndef KEY_EVENT_FILTER_H
#define KEY_EVENT_FILTER_H

#include <functional>
#include <map>
#include <set>

#include <QtCore/QObject>
#include <QtCore/QEvent>

class KeyEventFilter : public QObject
{
public:
  typedef std::function<void()> KeyListener;

  enum KeyListenerType
  {
    Single,
    Multi
  };

  bool isKeyPressed(int key) const;

  void addListener(int key, const KeyListener &listener, KeyListenerType type = Single);
  void removeListener(int key, const KeyListener &listener, KeyListenerType type = Single);

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  typedef std::multimap<int, KeyListener> KeyListenerMap;

  void addListener(int key, const KeyListener &listener, KeyListenerMap &listeners);
  void removeListener(int key, const KeyListener &listener, KeyListenerMap &listeners);
  void notifyListeners(int key, KeyListenerMap &listeners);

  std::set<int> pressedKeys;
  struct KeyListeners
  {
    KeyListenerMap single;
    KeyListenerMap multi;
  } keyListeners;
};

#endif