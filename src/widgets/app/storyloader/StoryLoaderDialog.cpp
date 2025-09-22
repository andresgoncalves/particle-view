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