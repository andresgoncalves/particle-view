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
  // Clear buffers
  renderContext.painter.beginNativePainting();
  glClearColor(
      renderContext.appContext.displayController.getBackgroundColor().redF(),
      renderContext.appContext.displayController.getBackgroundColor().greenF(),
      renderContext.appContext.displayController.getBackgroundColor().blueF(),
      1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  renderContext.painter.endNativePainting();

  auto containers = renderContext.appContext.containerController.getContainers();

  renderContext.painter.beginNativePainting();
  glEnable(GL_DEPTH_TEST);

  for (auto &particle : scene.particles)
  {
    particleRenderer->render(particle, renderContext);
    for (auto &property : particle.properties)
      vectorRenderer->render(particle, property.first, renderContext);
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
