#include "ContainerDialog.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

ContainerDialog::ContainerDialog(AppContext &appContext, QWidget *parent) : ContainerDialog{false, appContext, parent} {}

ContainerDialog::ContainerDialog(const Container &container, AppContext &appContext, QWidget *parent) : ContainerDialog{true, appContext, parent}
{
  originalContainer = container;
  nameControl->setValue(container.name);
  centerControl->setValue(container.center);
  sizeControl->setValue(container.size);
  rotationControl->setValue(container.rotation.toEulerAngles());
  auto shapeIndex = shapeComboBox->findData(static_cast<int>(container.shape));
  if (shapeIndex >= 0)
    shapeComboBox->setCurrentIndex(shapeIndex);
}

ContainerDialog::ContainerDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar contenedor" : "Agregar contenedor");

  nameControl = new TextControl{"Nombre", this};
  centerControl = new VectorControl{"Centro", this};
  sizeControl = new VectorControl{"Tamaño", {"Ancho:", "Alto:", "Profundidad:"}, this};
  rotationControl = new VectorControl{"Rotación:", {"x:", "y':", "z\":"}, this};
  shapeComboBox = new QComboBox{this};
  shapeComboBox->addItem("Cuboide", static_cast<int>(ContainerShape::Cuboid));
  shapeComboBox->addItem("Elipsoide", static_cast<int>(ContainerShape::Ellipsoid));

  auto controlLayout = new QVBoxLayout{};
  controlLayout->addWidget(shapeComboBox);
  controlLayout->addWidget(nameControl);
  controlLayout->addWidget(centerControl);
  controlLayout->addWidget(sizeControl);
  controlLayout->addWidget(rotationControl);
  controlLayout->setContentsMargins(8, 8, 8, 8);

  auto acceptButton = new QPushButton{"Aceptar", this};
  connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);

  auto cancelButton = new QPushButton{"Cancelar", this};
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(acceptButton);
  buttonLayout->addWidget(cancelButton);
  buttonLayout->setContentsMargins(8, 4, 8, 4);

  auto layout = new QVBoxLayout{this};
  layout->addLayout(controlLayout);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignRight);
  layout->setContentsMargins(0, 4, 0, 4);

  setMinimumWidth(320);
}

Container ContainerDialog::getContainer() const
{
  auto container = originalContainer.value_or(Container{});
  container.name = nameControl->getValue();
  container.center = centerControl->getValue();
  container.size = sizeControl->getValue();
  container.rotation = QQuaternion::fromEulerAngles(rotationControl->getValue());
  container.shape = static_cast<ContainerShape>(shapeComboBox->currentData().toInt());
  return container;
}