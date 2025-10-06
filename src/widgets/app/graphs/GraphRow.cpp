#include "GraphRow.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileDialog>

#include "GraphWidget.h"
#include "GraphWindow.h"
#include "GraphDialog.h"

GraphRow::GraphRow(GraphController::Graphs::iterator iterator, AppContext &appContext, QWidget *parent) : QWidget{parent}
{
  auto graph = *iterator;

  auto graphWindow = new GraphWindow{*graph, appContext, this};

  auto actionMenu = new QMenu{this};
  auto openAction = actionMenu->addAction("Abrir");
  connect(openAction, &QAction::triggered,
          [=, this]()
          { graphWindow->show(); });
  auto exportAction = actionMenu->addAction("Exportar");
  connect(exportAction, &QAction::triggered,
          [=, &appContext, this]()
          {
            auto fileName = QFileDialog::getSaveFileName(parent ? parent : this, "Seleccionar archivo", "", "Imagen PNG (*.png);;Todos los archivos (*)").toStdString();
            if (!fileName.empty())
            {
              if (!fileName.ends_with(".png"))
                fileName += ".png";
              // Render to image
              auto image = graphWindow->renderToImage({1280, 720}, *graph, appContext);
              image.save(fileName.c_str());
            }
          });
  auto editAction = actionMenu->addAction("Editar");
  connect(editAction, &QAction::triggered,
          [=, &appContext, this]()
          {
            auto dialog = new GraphDialog{*graph, appContext, this};
            if (dialog->exec() == QDialog::Accepted)
            {
              auto newGraph = std::make_shared<Graph>(dialog->getGraph());
              appContext.graphController.replaceGraph(iterator, newGraph);
            }
            dialog->deleteLater();
          });
  auto copyAction = actionMenu->addAction("Copiar");
  connect(copyAction, &QAction::triggered,
          [=, &appContext]()
          {
            auto newGraph = std::make_shared<Graph>(*graph);
            appContext.graphController.addGraph(newGraph);
          });
  auto deleteAction = actionMenu->addAction("Eliminar");
  connect(deleteAction, &QAction::triggered,
          [=, &appContext]()
          {
            appContext.graphController.removeGraph(iterator);
          });

  auto graphWidget = new GraphWidget{*graph, appContext.animationController.getStory(), this};
  graphWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(graphWidget, &QWidget::customContextMenuRequested, this, [=, this](QPoint position)
          { actionMenu->popup(mapToGlobal(position)); });

  auto label = new QLabel{graph->getTitle().c_str(), this};

  auto layout = new QVBoxLayout{this};
  layout->addWidget(label);
  layout->addWidget(graphWidget);
  layout->setContentsMargins({});

  setFixedHeight(320);
}
