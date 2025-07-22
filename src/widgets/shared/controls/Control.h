#ifndef CONTROL_H
#define CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QBoxLayout>

/** Base control with title and a child widget */
template <typename W = QWidget>
class Control : public QWidget
{
public:
  /** Creates a vertical control without title */
  Control(W *widget, QWidget *parent = nullptr) : Control{nullptr, widget, parent} {}

  /** Creates a vertical control with title */
  Control(const char *title, W *widget, QWidget *parent = nullptr) : Control{title, widget, QBoxLayout::Direction::Down, parent} {}

  /** Creates a control with title and given direction */
  Control(const char *title, W *widget, QBoxLayout::Direction direction, QWidget *parent = nullptr) : widget{widget}, QWidget{parent}
  {
    layout = new QBoxLayout{direction, this};

    label = new QLabel{title, this};
    label->setContentsMargins(4, 0, 4, 0);
    if (title != nullptr)
      layout->addWidget(label);
    else
      label->hide();

    layout->addWidget(widget);
    layout->setContentsMargins({});
  }

  /** Returns the control layout */
  QBoxLayout *getLayout() const
  {
    return layout;
  }

  /** Returns the control title */
  QLabel *getLabel() const
  {
    return label;
  }

  /** Returns the control widget */
  W *getWidget()
  {
    return widget;
  }

protected:
  QBoxLayout *layout;
  QLabel *label;
  W *widget;
};

#endif