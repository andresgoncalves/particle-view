#include "GraphWidget.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtWidgets/QVBoxLayout>

GraphWidget::GraphWidget(const Graph &graph, const Story &story, QWidget *parent) : QWidget{parent}
{
  auto series = new QScatterSeries{this};

  for (auto &[time, scene] : story.scenes)
  {
    auto value = graph.getValue(scene);
    if (value.has_value())
      series->append(value.value().first, value.value().second);
  }

  series->setBorderColor(QColor{0, 0, 0, 0});

  auto chart = new QChart{};
  chart->addSeries(series);
  chart->createDefaultAxes();
  for (auto &axis : chart->axes(Qt::Horizontal))
    axis->setTitleText(graph.getXAxis()->getText().c_str());
  for (auto &axis : chart->axes(Qt::Vertical))
    axis->setTitleText(graph.getYAxis()->getText().c_str());

  auto chartView = new QChartView{chart, this};
  chartView->setMinimumWidth(200);
  chartView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
  chartView->setContentsMargins({});

  auto layout = new QVBoxLayout{this};
  layout->addWidget(chartView);
  layout->setContentsMargins({});
}