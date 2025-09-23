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
  auto containers = renderContext.appContext.containerController.getContainers();

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

  for (auto container : containers)
  {
    auto containerRenderer = containerRenderers.find(container->shape);
    if (containerRenderer == containerRenderers.end())
    {
      containerRenderers.emplace(container->shape, container->shape);
      containerRenderer = containerRenderers.find(container->shape);
    }
    containerRenderer->second.render(*container, renderContext);
  }

  renderContext.painter.endNativePainting();
}
