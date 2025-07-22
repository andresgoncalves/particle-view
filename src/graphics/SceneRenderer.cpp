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
  auto displayParticles = appContext.displayController.getDisplayParticles();
  auto displayVectors = appContext.displayController.getDisplayVectors();

  if (displayParticles.first)
  {
    for (auto &particle : scene.particles)
      particleRenderer->render(particle, appContext);
  }

  for (auto [property, displayProperty] : displayVectors)
  {
    if (displayProperty.first)
    {
      for (auto &particle : scene.particles)
        vectorRenderer->render({particle, property}, appContext);
    }
  }
}
