#include "GraphWindow.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>

GraphWindow::GraphWindow(const Graph &graph, AppContext &appContext, QWidget *parent) : graph{graph}
{
  setWindowTitle(("Gráfico - " + graph.getTitle()).c_str());

  auto series = new QScatterSeries{this};
  for (auto &[time, scene] : appContext.animationController.getStory().scenes)
  {
    auto value = graph.getValue(scene);
    if (value.has_value())
      series->append(value.value().first, value.value().second);
  }
  series->setBorderColor(QColor{0, 0, 0, 0});

  auto xAxis = new QValueAxis{this};
  xAxis->setTitleText(graph.getXAxis()->getText().c_str());
  xAxis->setRange(graph.getXAxis()->getRange().first, graph.getXAxis()->getRange().second);

  auto yAxis = new QValueAxis{this};
  yAxis->setTitleText(graph.getYAxis()->getText().c_str());
  yAxis->setRange(graph.getYAxis()->getRange().first, graph.getYAxis()->getRange().second);

  auto chart = new QChart{};
  chart->addSeries(series);
  chart->addAxis(xAxis, Qt::AlignBottom);
  chart->addAxis(yAxis, Qt::AlignLeft);
  chart->setTitle(graph.getTitle().c_str());
  chart->legend()->hide();

  series->attachAxis(xAxis);
  series->attachAxis(yAxis);

  auto chartView = new QChartView{chart, this};
  chartView->setContentsMargins({});

  auto layout = new QVBoxLayout{this};
  layout->addWidget(chartView);
  layout->setContentsMargins({});

  setMinimumSize(400, 300);
}
