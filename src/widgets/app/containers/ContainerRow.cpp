#include "ContainerRow.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>

#include <widgets/shared/dialogs/ColorPicker.h>
#include <widgets/shared/buttons/ColorButton.h>

ContainerRow::ContainerRow(ContainerController::Containers::iterator iterator, AppContext &appContext, QWidget *parent) : QWidget{parent}
{
  auto container = *iterator;

  auto checkBox = new QCheckBox{this};
  checkBox->setChecked(container->enabled);
  connect(checkBox, &QCheckBox::checkStateChanged,
          [=, &appContext, this](Qt::CheckState checkState)
          {
            auto newContainer = std::make_shared<Container>(*container);
            newContainer->enabled = checkState != Qt::Unchecked;
            appContext.containerController.replaceContainer(iterator, newContainer);
          });

  auto label = new QLabel{container->name.c_str()};

  auto colorButton = new ColorButton{this};
  colorButton->setSolidColor(container->color);
  connect(colorButton, &QPushButton::clicked,
          [=, &appContext, this]()
          {
            auto color = ColorPicker::getColor(this);
            if (color.has_value())
            {
              auto newContainer = std::make_shared<Container>(*container);
              newContainer->color = color.value();
              appContext.containerController.replaceContainer(iterator, newContainer);
            }
          });

  auto actionMenu = new QMenu{this};
  auto editAction = actionMenu->addAction("Editar");
  connect(editAction, &QAction::triggered,
          [=, &appContext]()
          {
            // TODO: container dialog
          });
  auto copyAction = actionMenu->addAction("Copiar");
  connect(copyAction, &QAction::triggered,
          [=, &appContext]()
          {
            auto newContainer = std::make_shared<Container>(*container);
            appContext.containerController.addContainer(newContainer);
          });
  auto deleteAction = actionMenu->addAction("Eliminar");
  connect(deleteAction, &QAction::triggered,
          [=, &appContext]()
          {
            appContext.containerController.removeContainer(iterator);
          });

  auto actionsButton = new QPushButton{"⋮", this};
  connect(actionsButton, &QPushButton::clicked,
          [=, this]()
          {
            actionMenu->popup(mapToGlobal(actionsButton->pos() + QPoint{0, actionsButton->height()}));
          });

  auto layout = new QGridLayout{this};
  layout->setAlignment(Qt::AlignVCenter);
  layout->addWidget(checkBox, 0, 0);
  layout->addWidget(label, 0, 1);
  layout->addWidget(colorButton, 0, 2);
  layout->addWidget(actionsButton, 0, 3);
  layout->setContentsMargins({});

  layout->setColumnStretch(0, 0);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 0);
  layout->setHorizontalSpacing(16);
}
