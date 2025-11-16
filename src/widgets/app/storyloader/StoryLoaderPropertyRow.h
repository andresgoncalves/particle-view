#ifndef STORY_LOADER_PROPERTY_ROW
#define STORY_LOADER_PROPERTY_ROW

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

class StoryLoaderPropertyRow : public QWidget
{
public:
  virtual void setCount(int count) = 0;
  QPushButton *getActionsButton() const;

protected:
  StoryLoaderPropertyRow(const char *title, bool withActionsButton, QWidget *parent = nullptr);

  void setWidget(QWidget *widget);

private:
  QWidget *widget;
  QGridLayout *layout;
  QPushButton *actionsButton;
};

#endif