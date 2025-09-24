#ifndef CONTAINER_DIALOG_H
#define CONTAINER_DIALOG_H

#include <optional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/shared/controls/TextControl.h>
#include <widgets/shared/controls/VectorControl.h>

class ContainerDialog : public QDialog
{
public:
  ContainerDialog(AppContext &appContext, QWidget *parent = nullptr);
  ContainerDialog(const Container &container, AppContext &appContext, QWidget *parent = nullptr);

  Container getContainer() const;

private:
  ContainerDialog(bool edit, AppContext &appContext, QWidget *parent = nullptr);

  std::optional<Container> originalContainer;

  TextControl *nameControl;
  VectorControl *centerControl;
  VectorControl *sizeControl;
  VectorControl *rotationControl;
  QComboBox *shapeComboBox;
};

#endif