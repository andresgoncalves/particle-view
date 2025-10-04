#ifndef STRING_MATCHER_CONTROL_H
#define STRING_MATCHER_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/TextControl.h>

class StringMatcherValueControl : public QWidget
{
public:
  StringMatcherValueControl(QWidget *parent = nullptr);

  std::unique_ptr<ParticleMatcher> getMatcher(std::string propertyName) const;

private:
  enum class MatcherType
  {
    Equal,
    NotEqual
  };

  QComboBox *matcherTypeComboBox;
  TextControl *valueControl;
};

#endif