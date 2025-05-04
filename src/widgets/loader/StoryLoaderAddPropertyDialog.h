#ifndef STORY_LOADER_ADD_PROPERTY_DIALOG_H
#define STORY_LOADER_ADD_PROPERTY_DIALOG_H

#include <string>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>

#include "../../models/Particle.h"

class StoryLoaderAddPropertyDialog : public QDialog
{
public:
  StoryLoaderAddPropertyDialog(QWidget *parent = nullptr);

  std::string getProperty() const;
  Particle::PropertyType getType() const;

private:
  QLineEdit *propertyTextField;
  QComboBox *typeComboBox;
};

#endif