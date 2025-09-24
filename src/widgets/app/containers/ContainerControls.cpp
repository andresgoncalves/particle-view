#include "ContainerControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "ContainerList.h"
#include "ContainerDialog.h"

ContainerControls::ContainerControls(AppContext &appContext, QWidget *parent) : Section{"Contenedores", parent}
{
  auto containerList = new ContainerList{appContext, this};

  auto addButton = new QPushButton{"Agregar", this};
  auto addCallback = [=, &appContext, this]()
  {
    auto dialog = new ContainerDialog{appContext, this};
    if (dialog->exec() == QDialog::Accepted)
    {
      auto newContainer = std::make_shared<Container>(dialog->getContainer());
      appContext.containerController.addContainer(newContainer);
    }
    dialog->deleteLater();
  };
  connect(addButton, &QPushButton::clicked, this, addCallback);

  auto clearButton = new QPushButton{"Limpiar", this};
  connect(clearButton, &QPushButton::clicked, this,
          [&appContext]()
          { appContext.containerController.clearContainers(); });

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(clearButton);

  auto layout = new QVBoxLayout{content};
  layout->addWidget(containerList);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignRight);
  layout->setContentsMargins({});
}
