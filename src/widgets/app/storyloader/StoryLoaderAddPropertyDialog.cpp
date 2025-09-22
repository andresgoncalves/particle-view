#include "StoryLoaderAddPropertyDialog.h"

#include "StoryLoaderPropertyGrid.h"

StoryLoaderAddPropertyDialog::StoryLoaderAddPropertyDialog(QWidget *parent) : QDialog{parent}
{
  setWindowTitle("Agregar variable");

  propertyTextField = new QLineEdit{this};
  propertyTextField->setPlaceholderText("Nombre de la variable");

  typeComboBox = new QComboBox{this};
  typeComboBox->addItem("Escalar", static_cast<int>(PropertyType::Scalar));
  typeComboBox->addItem("Vector", static_cast<int>(PropertyType::Vector));
  typeComboBox->addItem("Texto", static_cast<int>(PropertyType::String));

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

PropertyType StoryLoaderAddPropertyDialog::getType() const
{
  return static_cast<PropertyType>(typeComboBox->currentData().toInt());
}