#include "GraphWindow.h"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>

GraphWindow::GraphWindow(const Graph &graph, AppContext &appContext, QWidget *parent) : graph{graph}
{
  setWindowTitle(("Gráfico - " + graph.getTitle()).c_str());

  auto chart = new QChart{};
  buildChart(chart, graph, appContext);

  auto chartView = new QChartView{chart, this};
  chartView->setRenderHint(QPainter::Antialiasing);
  chartView->setContentsMargins({});

  auto layout = new QVBoxLayout{this};
  layout->addWidget(chartView);
  layout->setContentsMargins({});

  setMinimumSize(400, 300);
}

QImage GraphWindow::renderToImage(QSize size, const Graph &graph, AppContext &appContext) const
{
  auto chart = new QChart{};
  buildChart(chart, graph, appContext);
  chart->setBackgroundRoundness(0);
  chart->resize(size);

  // Render to image
  auto image = QImage{size, QImage::Format_ARGB32};
  image.fill(Qt::transparent);

  auto painter = QPainter{&image};
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::TextAntialiasing, true);

  auto graphicsScene = QGraphicsScene{};
  graphicsScene.addItem(chart);
  graphicsScene.setSceneRect({{}, size});
  graphicsScene.render(&painter);

  return image;
}

void GraphWindow::buildChart(QChart *chart, const Graph &graph, AppContext &appContext) const
{
  auto series = new QScatterSeries{chart};
  for (auto &[time, scene] : appContext.animationController.getStory().scenes)
  {
    auto value = graph.getValue(scene);
    if (value.has_value())
      series->append(value.value().first, value.value().second);
  }
  series->setBorderColor(QColor{0, 0, 0, 0});

  auto xAxis = new QValueAxis{chart};
  xAxis->setTitleText(graph.getXAxis()->getText().c_str());
  xAxis->setRange(graph.getXAxis()->getRange().first, graph.getXAxis()->getRange().second);

  auto yAxis = new QValueAxis{chart};
  yAxis->setTitleText(graph.getYAxis()->getText().c_str());
  yAxis->setRange(graph.getYAxis()->getRange().first, graph.getYAxis()->getRange().second);

  chart->addSeries(series);
  chart->addAxis(xAxis, Qt::AlignBottom);
  chart->addAxis(yAxis, Qt::AlignLeft);
  chart->setTitle(graph.getTitle().c_str());
  chart->legend()->hide();

  series->attachAxis(xAxis);
  series->attachAxis(yAxis);
}
