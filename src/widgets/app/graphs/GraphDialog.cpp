#include "GraphDialog.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

#include <controllers/graphs/ScalarSceneGraphAxis.h>
#include <controllers/graphs/VectorSceneGraphAxis.h>
#include <widgets/shared/dialogs/ColorPicker.h>

GraphDialog::GraphDialog(AppContext &appContext, QWidget *parent) : GraphDialog{false, appContext, parent} {}

GraphDialog::GraphDialog(const Graph &graph, AppContext &appContext, QWidget *parent) : GraphDialog{true, appContext, parent}
{
  originalGraph = graph;

  // Set X axis property
  if (auto scalarXAxis = dynamic_cast<ScalarSceneGraphAxis *>(graph.getXAxis().get()))
    xPropertyControl->setValue({scalarXAxis->getPropertyName(), PropertyType::Scalar, {}});
  if (auto vectorXAxis = dynamic_cast<VectorSceneGraphAxis *>(graph.getXAxis().get()))
    xPropertyControl->setValue({vectorXAxis->getPropertyName(), PropertyType::Vector, vectorXAxis->getVectorComponent()});

  // Set Y axis property
  if (auto scalarYAxis = dynamic_cast<ScalarSceneGraphAxis *>(graph.getYAxis().get()))
    yPropertyControl->setValue({scalarYAxis->getPropertyName(), PropertyType::Scalar, {}});
  if (auto vectorYAxis = dynamic_cast<VectorSceneGraphAxis *>(graph.getYAxis().get()))
    yPropertyControl->setValue({vectorYAxis->getPropertyName(), PropertyType::Vector, vectorYAxis->getVectorComponent()});
}

GraphDialog::GraphDialog(bool edit, AppContext &appContext, QWidget *parent) : QDialog{parent}
{
  setWindowTitle(edit ? "Editar gráfico" : "Agregar gráfico");

  xPropertyControl = new PropertyControl{"Eje X:", appContext.animationController.getStory().metadata.sceneProperties, this};
  yPropertyControl = new PropertyControl{"Eje Y:", appContext.animationController.getStory().metadata.sceneProperties, this};

  auto controlLayout = new QVBoxLayout{};
  controlLayout->addWidget(xPropertyControl);
  controlLayout->addWidget(yPropertyControl);
  controlLayout->addStretch();
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

Graph GraphDialog::getGraph() const
{
  auto xProperty = xPropertyControl->getValue();
  auto yProperty = yPropertyControl->getValue();

  auto xAxis = getGraphAxis(std::get<0>(xProperty), std::get<1>(xProperty), std::get<2>(xProperty));
  auto yAxis = getGraphAxis(std::get<0>(yProperty), std::get<1>(yProperty), std::get<2>(yProperty));

  auto graph = Graph{std::move(xAxis), std::move(yAxis)};

  return graph;
}

std::unique_ptr<GraphAxis<float>> GraphDialog::getGraphAxis(std::string propertyName, PropertyType propertyType, VectorComponent vectorComponent) const
{
  switch (propertyType)
  {
  case PropertyType::Scalar:
    return std::make_unique<ScalarSceneGraphAxis>(propertyName);
  case PropertyType::Vector:
    return std::make_unique<VectorSceneGraphAxis>(propertyName, vectorComponent);
  case PropertyType::String:
    // TODO: handle string case
    return std::make_unique<VectorSceneGraphAxis>(propertyName, vectorComponent);
  }
}