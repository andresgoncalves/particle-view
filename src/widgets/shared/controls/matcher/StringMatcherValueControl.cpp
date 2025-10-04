#include "StringMatcherValueControl.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include <controllers/matchers/StringParticleMatcher.h>

StringMatcherValueControl::StringMatcherValueControl(QWidget *parent) : QWidget{parent}
{
  matcherTypeComboBox = new QComboBox{this};
  matcherTypeComboBox->addItem("=", static_cast<int>(MatcherType::Equal));
  matcherTypeComboBox->addItem("≠", static_cast<int>(MatcherType::NotEqual));

  valueControl = new TextControl{this};

  auto layout = new QHBoxLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(matcherTypeComboBox);
  layout->addWidget(valueControl);
  layout->setContentsMargins({});
}

void StringMatcherValueControl::setMatcher(const AbstractStringBinaryParticleMatcher *matcher)
{
  matcherTypeComboBox->setCurrentText(matcher->getSymbol().c_str());
  valueControl->setValue(matcher->getReferenceValue());
}

std::unique_ptr<ParticleMatcher> StringMatcherValueControl::getMatcher(std::string propertyName) const
{
  auto matcherFactory = StringParticleMatcherFactory{propertyName};
  auto matcherType = static_cast<MatcherType>(matcherTypeComboBox->currentData().toInt());
  auto value = valueControl->getValue();
  switch (matcherType)
  {
  case MatcherType::Equal:
    return matcherFactory.equal(value);
  case MatcherType::NotEqual:
    return matcherFactory.notEqual(value);
  }
}
