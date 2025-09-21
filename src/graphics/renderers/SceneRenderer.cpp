#include <QtGui/QMatrix4x4>

#include "SceneRenderer.h"
#include "ParticleRenderer.h"
#include "VectorRenderer.h"

SceneRenderer::SceneRenderer()
{
  particleRenderer = std::make_unique<ParticleRenderer>();
  vectorRenderer = std::make_unique<VectorRenderer>();
}

void SceneRenderer::render(const Scene &scene, RenderContext &renderContext)
{
  auto displayParticles = renderContext.appContext.displayController.getDisplayParticles();
  auto displayVectors = renderContext.appContext.displayController.getDisplayVectors();

  renderContext.painter.beginNativePainting();
  glEnable(GL_DEPTH_TEST);

  if (displayParticles.first)
  {
    for (auto &particle : scene.particles)
      particleRenderer->render(particle, renderContext);
  }

  for (auto [property, displayProperty] : displayVectors)
  {
    if (displayProperty.first)
      for (auto &particle : scene.particles)
        vectorRenderer->render(particle, property, renderContext);
  }

  renderContext.painter.endNativePainting();
}
