#include <QtGui/QMatrix4x4>

#include "SceneRenderer.h"

SceneRenderer::SceneRenderer()
{
  particleRenderer = std::make_unique<ParticleRenderer>();
}

void SceneRenderer::render(const Scene &scene, const RenderController &renderController)
{
  for (auto &particle : scene.particles)
  {
    particleRenderer->render(particle, renderController);
  }
}
