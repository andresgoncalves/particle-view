#ifndef GENERIC_SHADER_H
#define GENERIC_SHADER_H

#include <memory>

#include <QtGui/QColor>
#include <QtGui/QVector4D>
#include <QtGui/QMatrix4x4>
#include <QtOpenGL/QOpenGLShaderProgram>

class GenericShader
{
public:
  /** Bind shader */
  void bind();

  /** Set color uniform */
  virtual void setColor(const QColor &color);

  /** Set color uniform */
  virtual void setColor(const QVector4D &color);

  /** Set matrix uniform */
  virtual void setMatrix(const QMatrix4x4 &matrix);

  /** Get current instance */
  static GenericShader *getInstance();

private:
  /** Private constructor */
  GenericShader();

  /** Shader program */
  QOpenGLShaderProgram shaderProgram;

  /** Current instance */
  static GenericShader *instance;
};

#endif