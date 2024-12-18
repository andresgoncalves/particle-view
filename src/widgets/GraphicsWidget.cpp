#include "GraphicsWidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void GraphicsWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GraphicsWidget::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
}

void GraphicsWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, 0.5f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glEnd();
}
