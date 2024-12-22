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
  bool isKeyPressed(int key) const;

  void addListener(int key, const std::function<void()> listener);
  void removeListener(int key, const std::function<void()> listener);

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  std::set<int> pressedKeys;
  std::multimap<int, std::function<void()>> keyListeners;
};

#endif