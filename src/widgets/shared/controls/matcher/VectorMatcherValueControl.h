#ifndef VECTOR_MATCHER_CONTROL_H
#define VECTOR_MATCHER_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <controllers/matchers/VectorParticleMatcher.h>
#include <widgets/shared/controls/NumericControl.h>

class VectorMatcherValueControl : public QWidget
{
public:
  VectorMatcherValueControl(QWidget *parent = nullptr);

  void setMatcher(const AbstractVectorBinaryParticleMatcher *matcher);

  std::unique_ptr<ParticleMatcher> getMatcher(std::string propertyName, VectorComponent vectorComponent) const;

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