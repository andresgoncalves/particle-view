#include "StoryLoaderDialog.h"

#include <fstream>
#include <filesystem>

#include <QtWidgets/QtWidgets>

#include "StoryLoaderPropertyGrid.h"
#include "StoryLoaderAddPropertyDialog.h"
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

  int initialCount = 7;

  propertyGrid = new StoryLoaderPropertyGrid{this};
  propertyGrid->setCount(initialCount);

  auto columnControl = new NumericControl{"Cantidad de columnas", this};
  columnControl->getLayout()->setDirection(QBoxLayout::Direction::LeftToRight);
  columnControl->setValue(initialCount);
  columnControl->onChange<int>([&](int value)
                               { propertyGrid->setCount(value); });

  auto addPropertyButton = new QPushButton{"Agregar variable", this};
  auto addPropertyCallback = [=, this]
  {
    auto addPropertyDialog = new StoryLoaderAddPropertyDialog{this};
    if (addPropertyDialog->exec() == QDialog::Accepted)
    {
      propertyGrid->addCustomProperty(addPropertyDialog->getProperty(), addPropertyDialog->getType());
    }
    addPropertyDialog->deleteLater();
  };
  connect(addPropertyButton, &QPushButton::clicked, this, addPropertyCallback);

  auto loadButton = new QPushButton{"Cargar", this};
  auto loadCallback = [&]()
  {
    auto fileName = selectFileTextField->text().toStdString();
    if (!std::filesystem::exists(fileName) || !std::filesystem::is_regular_file(fileName))
    {
      QMessageBox{QMessageBox::Icon::Critical, "Error", "Archivo no encontrado"}.exec();
      return;
    }

    auto loader = StoryLoader{
        .defaultProperties = propertyGrid->getDefaultProperties(),
        .scalarProperties = propertyGrid->getScalarProperties(),
        .vectorProperties = propertyGrid->getVectorProperties(),
    };

    auto input = std::ifstream{fileName};

    auto story = loader.load(input);

    appContext.animationController.setStory(story);
    appContext.viewController.setOrigin((story.metadata.start + story.metadata.end) / 2);

    auto diagonalSize = story.metadata.start.distanceToPoint(story.metadata.end);
    appContext.viewController.setBaseScale(diagonalSize > 0 ? 1.f / diagonalSize : 1.f);

    accept();
  };
  connect(loadButton, &QPushButton::clicked, this, loadCallback);

  auto buttonsLayout = new QHBoxLayout{};
  buttonsLayout->setAlignment(Qt::AlignRight);
  buttonsLayout->addWidget(addPropertyButton);
  buttonsLayout->addWidget(loadButton);

  auto verticalLayout = new QVBoxLayout{this};
  verticalLayout->addWidget(selectFileLabel);
  verticalLayout->addLayout(horizontalLayout);
  verticalLayout->addWidget(columnControl);
  verticalLayout->addWidget(propertyGrid);
  verticalLayout->addLayout(buttonsLayout);

  setMinimumWidth(320);
}
