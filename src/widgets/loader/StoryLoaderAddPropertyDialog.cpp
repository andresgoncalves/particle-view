#include "StoryLoaderAddPropertyDialog.h"

#include <QtWidgets/QtWidgets>

#include "StoryLoaderPropertyGrid.h"

StoryLoaderAddPropertyDialog::StoryLoaderAddPropertyDialog(QWidget *parent) : QDialog{parent}
{
  setWindowTitle("Agregar variable");

  propertyTextField = new QLineEdit{this};
  propertyTextField->setPlaceholderText("Nombre de la variable");

  typeComboBox = new QComboBox{this};
  typeComboBox->addItem("Escalar", Particle::PropertyType::Scalar);
  typeComboBox->addItem("Vector", Particle::PropertyType::Vector);

  auto addButton = new QPushButton{"Agregar", this};
  connect(addButton, &QPushButton::clicked, this, [=, this]
          { this->accept(); });
  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, [=, this]
          { this->reject(); });

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(cancelButton);
  buttonsLayout->addWidget(addButton);

  auto layout = new QVBoxLayout{this};
  layout->addWidget(propertyTextField);
  layout->addWidget(typeComboBox);
  layout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

std::string StoryLoaderAddPropertyDialog::getProperty() const
{
  return propertyTextField->text().toStdString();
}

Particle::PropertyType StoryLoaderAddPropertyDialog::getType() const
{
  return static_cast<Particle::PropertyType>(typeComboBox->currentData().toInt());
}