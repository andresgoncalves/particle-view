#include "GenericShader.h"

inline const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "uniform vec3 color;\n"
    "uniform mat4 matrix;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = matrix * vec4(position, 1.0f);\n"
    "}\n";

inline const char *fragmentShaderSource =
    "#version 330 core\n"
    "uniform vec4 color;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "    fragmentColor = color;\n"
    "}\n";

GenericShader *GenericShader::instance = nullptr;

GenericShader::GenericShader()
{
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram.link();
}

void GenericShader::bind()
{
  shaderProgram.bind();
}

void GenericShader::setColor(const QColor &color)
{
  shaderProgram.setUniformValue("color", color);
}

void GenericShader::setColor(const QVector4D &color)
{
  shaderProgram.setUniformValue("color", color);
}

void GenericShader::setMatrix(const QMatrix4x4 &matrix)
{
  shaderProgram.setUniformValue("matrix", matrix);
}

GenericShader *GenericShader::getInstance()
{
  if (auto currentInstance = instance)
  {
    return currentInstance;
  }
  instance = new GenericShader{};
  return instance;
}
