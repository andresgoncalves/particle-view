#include <QtGui/QMatrix4x4>

#include "SceneRenderer.h"
#include "ParticleRenderer.h"
#include "VelocityRenderer.h"

SceneRenderer::SceneRenderer()
{
  particleRenderer = std::make_unique<ParticleRenderer>();
  velocityRenderer = std::make_unique<VelocityRenderer>();
}

void SceneRenderer::render(const Scene &scene, const AppContext &appContext)
{
  // for (auto &particle : scene.particles)
  //   particleRenderer->render(particle, appContext);

  for (auto &particle : scene.particles)
    velocityRenderer->render(particle, appContext);
}
