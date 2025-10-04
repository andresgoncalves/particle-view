#include "VectorMatcherValueControl.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include <controllers/matchers/VectorParticleMatcher.h>

VectorMatcherValueControl::VectorMatcherValueControl(QWidget *parent) : QWidget{parent}
{
  matcherTypeComboBox = new QComboBox{this};
  matcherTypeComboBox->addItem("=", static_cast<int>(MatcherType::Equal));
  matcherTypeComboBox->addItem("≠", static_cast<int>(MatcherType::NotEqual));
  matcherTypeComboBox->addItem("<", static_cast<int>(MatcherType::Less));
  matcherTypeComboBox->addItem(">", static_cast<int>(MatcherType::Greater));
  matcherTypeComboBox->addItem("≤", static_cast<int>(MatcherType::LessOrEqual));
  matcherTypeComboBox->addItem("≥", static_cast<int>(MatcherType::GreaterOrEqual));

  valueControl = new NumericControl{this};

  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(matcherTypeComboBox);
  layout->addWidget(valueControl);
  layout->setContentsMargins({});
}

std::unique_ptr<ParticleMatcher> VectorMatcherValueControl::getMatcher(std::string propertyName, VectorComponent vectorComponent) const
{
  auto matcherFactory = VectorParticleMatcherFactory{propertyName, vectorComponent};
  auto matcherType = static_cast<MatcherType>(matcherTypeComboBox->currentData().toInt());
  auto value = valueControl->getValue<float>();
  switch (matcherType)
  {
  case MatcherType::Equal:
    return matcherFactory.equal(value);
  case MatcherType::NotEqual:
    return matcherFactory.notEqual(value);
  case MatcherType::Less:
    return matcherFactory.less(value);
  case MatcherType::Greater:
    return matcherFactory.greater(value);
  case MatcherType::LessOrEqual:
    return matcherFactory.lessOrEqual(value);
  case MatcherType::GreaterOrEqual:
    return matcherFactory.greaterOrEqual(value);
  }
}
