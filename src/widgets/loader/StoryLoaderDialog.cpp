#include "StoryLoaderDialog.h"

#include <fstream>
#include <filesystem>
#include <QtWidgets/QtWidgets>

#include "StoryLoaderPropertyGrid.h"

StoryLoaderDialog::StoryLoaderDialog(AppContext &appContext, QWidget *parent) : appContext{appContext}, QDialog{parent}
{
  setWindowTitle("Cargar datos");

  selectFileTextField = new QLineEdit{this};

  auto selectFileLabel = new QLabel{"Seleccionar archivo", this};
  auto selectFileButton = new QPushButton{"Buscar", this};
  auto selectFileCallback = [&]()
  {
    auto fileName = QFileDialog::getOpenFileName(this, "Seleccionar archivo", selectFileTextField->text());
    if (!fileName.isEmpty())
    {
      selectFileTextField->setText(fileName);
    }
  };
  connect(selectFileButton, &QPushButton::clicked, this, selectFileCallback);

  auto horizontalLayout = new QHBoxLayout{};
  horizontalLayout->addWidget(selectFileTextField);
  horizontalLayout->addWidget(selectFileButton);

  propertyGrid = new StoryLoaderPropertyGrid{this};
  propertyGrid->setCount(7);

  auto loadButton = new QPushButton{"Cargar", this};
  auto loadCallback = [&]()
  {
    auto loader = StoryLoader{};
    loader.setColumnCount(7);

    auto defaultProperties = propertyGrid->getDefaultProperties();
    for (auto [property, value] : defaultProperties)
    {
      loader.setDefaultProperty(property, value);
    }

    auto fileName = selectFileTextField->text().toStdString();
    if (!std::filesystem::exists(fileName) || !std::filesystem::is_regular_file(fileName))
    {
      return;
    }

    auto input = std::ifstream{fileName};

    auto story = loader.load(input);
    appContext.animationController.setStory(story);

    accept();
  };
  connect(loadButton, &QPushButton::clicked, this, loadCallback);

  auto verticalLayout = new QVBoxLayout{this};
  verticalLayout->addWidget(selectFileLabel);
  verticalLayout->addLayout(horizontalLayout);
  verticalLayout->addWidget(propertyGrid);
  verticalLayout->addWidget(loadButton);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  setMinimumWidth(320);
  setFixedHeight(sizeHint().height());
}
