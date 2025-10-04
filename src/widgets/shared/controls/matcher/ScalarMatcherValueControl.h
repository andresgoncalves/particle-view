#ifndef SCALAR_MATCHER_CONTROL_H
#define SCALAR_MATCHER_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <controllers/matchers/ScalarParticleMatcher.h>
#include <widgets/shared/controls/NumericControl.h>

class ScalarMatcherValueControl : public QWidget
{
public:
  ScalarMatcherValueControl(QWidget *parent = nullptr);

  void setMatcher(const AbstractScalarBinaryParticleMatcher *matcher);

  std::unique_ptr<ParticleMatcher> getMatcher(std::string propertyName) const;

private:
  enum class MatcherType
  {
    Equal,
    NotEqual,
    Less,
    Greater,
    LessOrEqual,
    GreaterOrEqual,
  };

  QComboBox *matcherTypeComboBox;
  NumericControl *valueControl;
};

#endif