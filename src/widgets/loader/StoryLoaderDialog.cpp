#include "StoryLoaderDialog.h"

#include <fstream>
#include <filesystem>
#include <QtWidgets/QtWidgets>

#include "StoryLoaderPropertyGrid.h"
#include "../controls/NumericControl.h"

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

  auto columnControl = new NumericControl{"Cantidad de columnas", this};
  columnControl->getLayout()->setDirection(QBoxLayout::Direction::LeftToRight);
  columnControl->setValue(0);
  columnControl->onChange<int>([&](int value)
                               { propertyGrid->setCount(value); });

  auto loadButton = new QPushButton{"Cargar", this};
  auto loadCallback = [&]()
  {
    auto fileName = selectFileTextField->text().toStdString();
    if (!std::filesystem::exists(fileName) || !std::filesystem::is_regular_file(fileName))
    {
      QMessageBox{QMessageBox::Icon::Critical, "Error", "Archivo no encontrado"}.exec();
      return;
    }

    auto loader = StoryLoader{};
    loader.setColumnCount(7);

    for (auto [property, value] : propertyGrid->getDefaultProperties())
      loader.setDefaultProperty(property, value);
    for (auto [property, value] : propertyGrid->getCustomProperties())
      loader.setCustomProperty(property, value);

    auto input = std::ifstream{fileName};

    auto story = loader.load(input);
    appContext.animationController.setStory(story);

    accept();
  };
  connect(loadButton, &QPushButton::clicked, this, loadCallback);

  auto verticalLayout = new QVBoxLayout{this};
  verticalLayout->addWidget(selectFileLabel);
  verticalLayout->addLayout(horizontalLayout);
  verticalLayout->addWidget(columnControl);
  verticalLayout->addWidget(propertyGrid);
  verticalLayout->addWidget(loadButton);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  setMinimumWidth(320);
  setFixedHeight(sizeHint().height());
}
