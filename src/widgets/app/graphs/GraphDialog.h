#ifndef GRAPH_DIALOG_H
#define GRAPH_DIALOG_H

#include <optional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QRadioButton>

#include <controllers/AppContext.h>
#include <widgets/shared/buttons/ColorButton.h>
#include <widgets/shared/controls/TextControl.h>
#include <widgets/shared/controls/NumericControl.h>
#include <widgets/shared/controls/PropertyControl.h>

class GraphDialog : public QDialog
{
public:
  GraphDialog(AppContext &appContext, QWidget *parent = nullptr);
  GraphDialog(const Graph &graph, AppContext &appContext, QWidget *parent = nullptr);

  Graph getGraph() const;

private:
  GraphDialog(bool edit, AppContext &appContext, QWidget *parent = nullptr);

  std::unique_ptr<GraphAxis> getGraphAxis(std::string propertyName, PropertyType propertyType, VectorComponent vectorComponent = VectorComponent::Magnitude) const;

  std::optional<Graph> originalGraph;

  TextControl *titleControl;
  PropertyControl *xPropertyControl;
  PropertyControl *yPropertyControl;
  NumericControl *xRangeMin;
  NumericControl *xRangeMax;
  NumericControl *yRangeMin;
  NumericControl *yRangeMax;
};

#endif