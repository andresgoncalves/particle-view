#include "Story.h"

QVector3D Story::getOrigin() const
{
  return (metadata.start + metadata.end) / 2;
}

float Story::getBaseScale() const
{
  auto diagonalSize = metadata.start.distanceToPoint(metadata.end);
  return diagonalSize > 0.0f ? 1.0f / diagonalSize : 1.0f;
}