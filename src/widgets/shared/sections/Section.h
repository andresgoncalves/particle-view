#ifndef SECTION_H
#define SECTION_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

/** Layout section */
class Section : public QWidget
{
public:
  /** Create a section without title */
  Section(QWidget *parent);
  /** Create a section with title */
  Section(const char *title, QWidget *parent);

  /** Get content widget */
  QWidget *getContent();

protected:
  /** Content widget */
  QWidget *content;
};

#endif