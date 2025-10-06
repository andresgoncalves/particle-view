#include "GraphRow.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>

#include "GraphWidget.h"
#include "GraphDialog.h"

GraphRow::GraphRow(GraphController::Graphs::iterator iterator, AppContext &appContext, QWidget *parent) : QWidget{parent}
{
  auto graph = *iterator;

  auto actionMenu = new QMenu{this};
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

  auto layout = new QGridLayout{this};
  layout->setAlignment(Qt::AlignTop);
  layout->addWidget(graphWidget, 0, 0);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 1);
  layout->setHorizontalSpacing(16);
}
