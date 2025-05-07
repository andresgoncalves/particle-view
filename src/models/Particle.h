#ifndef PARTICLE_H
#define PARTICLE_H

#include <map>
#include <QtGui/QVector3D>

struct Particle
{
  inline static const std::string radiusProperty = "Radio";

  enum PropertyType
  {
    Scalar,
    Vector
  };

  QVector3D position = {0.0f, 0.0f, 0.0f};
  float radius = 1.0f;

  std::map<std::string, float> scalarProperties;
  std::map<std::string, QVector3D> vectorProperties;
};

#endif