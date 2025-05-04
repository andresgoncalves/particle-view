#ifndef STORY_LOADER_ADD_PROPERTY_DIALOG_H
#define STORY_LOADER_ADD_PROPERTY_DIALOG_H

#include <string>

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>

class StoryLoaderAddPropertyDialog : public QDialog
{
public:
  enum PropertyType
  {
    Scalar,
    Vector
  };

  StoryLoaderAddPropertyDialog(QWidget *parent = nullptr);

  std::string getProperty() const;
  PropertyType getType() const;

private:
  QLineEdit *propertyTextField;
  QComboBox *typeComboBox;
};

#endif