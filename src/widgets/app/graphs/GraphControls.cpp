#include "GraphControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

#include "GraphList.h"
#include "GraphDialog.h"

GraphControls::GraphControls(AppContext &appContext, QWidget *parent) : Section{"Gráficos", parent}
{
  auto containerList = new GraphList{appContext, this};

  auto addButton = new QPushButton{"Agregar", this};
  auto addCallback = [=, &appContext, this]()
  {
    auto dialog = new GraphDialog{appContext, this};
    if (dialog->exec() == QDialog::Accepted)
    {
      auto newGraph = std::make_shared<Graph>(dialog->getGraph());
      appContext.graphController.addGraph(newGraph);
    }
    dialog->deleteLater();
  };
  connect(addButton, &QPushButton::clicked, this, addCallback);

  auto clearButton = new QPushButton{"Limpiar", this};
  connect(clearButton, &QPushButton::clicked, this,
          [&appContext]()
          { appContext.graphController.clearGraphs(); });

  auto buttonLayout = new QHBoxLayout{};
  buttonLayout->addWidget(addButton);
  buttonLayout->addWidget(clearButton);

  auto layout = new QVBoxLayout{content};
  layout->addWidget(containerList);
  layout->addLayout(buttonLayout);
  layout->setAlignment(buttonLayout, Qt::AlignRight);
  layout->setContentsMargins({});
}
