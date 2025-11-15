#include "StoryLoaderDialog.h"

#include <fstream>
#include <filesystem>

#include <QtWidgets/QtWidgets>

#include <widgets/shared/controls/NumericControl.h>

#include "StoryLoaderPropertyGrid.h"
#include "StoryLoaderAddPropertyDialog.h"

StoryLoaderDialog::StoryLoaderDialog(AppContext &appContext, QWidget *parent) : StoryLoaderDialog{0, 0, appContext, parent}
{
}

StoryLoaderDialog::StoryLoaderDialog(int sceneColumnCount, int particleColumnCount, AppContext &appContext, QWidget *parent) : appContext{appContext}, QDialog{parent}
{
  setWindowTitle("Cargar datos");

  dimensionality2DButton = new QRadioButton{"2D", this};
  dimensionality3DButton = new QRadioButton{"3D", this};
  dimensionality3DButton->setChecked(true);
  connect(dimensionality2DButton, &QRadioButton::toggled,
          [=](bool isDimensionality2D)
          {
            // TODO: hide Z component in inputs
          });

  auto dimensionalityLayout = new QHBoxLayout{};
  dimensionalityLayout->setAlignment(Qt::AlignCenter);
  dimensionalityLayout->addWidget(dimensionality2DButton);
  dimensionalityLayout->addWidget(dimensionality3DButton);
  dimensionalityLayout->setContentsMargins(8, 8, 8, 8);

  scenePropertyGrid = new StoryLoaderPropertyGrid{this};
  scenePropertyGrid->setCount(sceneColumnCount);
  scenePropertyGrid->addProperty(Scene::PARTICLE_COUNT_PROPERTY, PropertyType::Scalar, false);
  scenePropertyGrid->addProperty(Scene::TIME_PROPERTY, PropertyType::Scalar, false);

  particlePropertyGrid = new StoryLoaderPropertyGrid{this};
  particlePropertyGrid->setCount(particleColumnCount);
  particlePropertyGrid->addProperty(Particle::POSITION_PROPERTY, PropertyType::Vector, false);
  particlePropertyGrid->addProperty(Particle::RADIUS_PROPERTY, PropertyType::Scalar, false);

  auto tabWidget = new QTabWidget{this};
  tabWidget->addTab(scenePropertyGrid, "Encabezado");
  tabWidget->addTab(particlePropertyGrid, "Partículas");

  auto loadButton = new QPushButton{"Cargar", this};
  connect(loadButton, &QPushButton::clicked, this, &QDialog::accept);

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setContentsMargins(8, 4, 8, 4);
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(loadButton);

  auto verticalLayout = new QVBoxLayout{this};
  verticalLayout->setContentsMargins(0, 4, 0, 4);
  verticalLayout->addLayout(dimensionalityLayout);
  verticalLayout->addWidget(tabWidget);
  verticalLayout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}

StoryLoader::PropertyDefinitionMap StoryLoaderDialog::getParticleProperties() const
{
  return particlePropertyGrid->getProperties();
}

StoryLoader::PropertyDefinitionMap StoryLoaderDialog::getSceneProperties() const
{
  return scenePropertyGrid->getProperties();
}

ViewController::Dimensionality StoryLoaderDialog::getDimensionality() const
{
  return dimensionality2DButton->isChecked() ? ViewController::Dimensionality::Dimension2D : ViewController::Dimensionality::Dimension3D;
}