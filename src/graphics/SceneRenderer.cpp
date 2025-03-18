#include <QtGui/QMatrix4x4>

#include "SceneRenderer.h"
#include "ParticleRenderer.h"

SceneRenderer::SceneRenderer()
{
  particleRenderer = std::make_unique<ParticleRenderer>();
}

void SceneRenderer::render(const Scene &scene, const ViewController &viewController)
{
  for (auto &particle : scene.particles)
  {
    particleRenderer->render(particle, viewController);
  }
}
