#ifndef VIEW_TRANSLATION_CONTROLS_H
#define VIEW_TRANSLATION_CONTROLS_H

#include <QtWidgets/QWidget>

#include <widgets/shared/sections/Section.h>
#include <controllers/AppContext.h>

/** View translation controls */
class ViewTranslationControls : public Section
{
public:
  /** Creates the translation controls */
  ViewTranslationControls(AppContext &appContext, QWidget *parent = nullptr);
  ~ViewTranslationControls();

private:
  /** Application context */
  AppContext &appContext;
};

#endif