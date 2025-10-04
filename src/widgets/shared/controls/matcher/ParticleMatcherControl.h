#ifndef PARTICLE_MATCHER_CONTROL_H
#define PARTICLE_MATCHER_CONTROL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include "ScalarMatcherValueControl.h"
#include "VectorMatcherValueControl.h"
#include "StringMatcherValueControl.h"

class ParticleMatcherControl : public QWidget
{
public:
  ParticleMatcherControl(const PropertyTypeMap &properties, QWidget *parent = nullptr);

  std::unique_ptr<ParticleMatcher> getMatcher() const;

private:
  QComboBox *propertyComboBox;
  ScalarMatcherValueControl *scalarMatcherValueControl;
  VectorMatcherValueControl *vectorMatcherValueControl;
  StringMatcherValueControl *stringMatcherValueControl;

  /** Property combo box values */
  std::vector<std::tuple<std::string, PropertyType, VectorComponent>> propertyValues;
};

#endif