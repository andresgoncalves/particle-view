#include <QtGui/QMatrix4x4>

#include "SceneRenderer.h"
#include "ParticleRenderer.h"
#include "VectorRenderer.h"

SceneRenderer::SceneRenderer()
{
  particleRenderer = std::make_unique<ParticleRenderer>();
  vectorRenderer = std::make_unique<VectorRenderer>();
}

void SceneRenderer::render(const Scene &scene, const AppContext &appContext)
{
  // for (auto &particle : scene.particles)
  //   particleRenderer->render(particle, appContext);

  for (auto &particle : scene.particles)
    vectorRenderer->render({particle, Particle::VelocityProperty}, appContext);
}
