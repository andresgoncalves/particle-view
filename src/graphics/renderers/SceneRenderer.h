#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include <memory>
#include <map>

#include <QtGui/QImage>

#include <models/Scene.h>
#include <controllers/ViewController.h>
#include <controllers/ViewController.h>
#include <graphics/renderers/ParticleRenderer.h>
#include <graphics/renderers/VectorRenderer.h>
#include <graphics/renderers/TimeRenderer.h>
#include <graphics/renderers/AxesRenderer.h>
#include <graphics/renderers/ColorScaleRenderer.h>
#include <graphics/renderers/ContainerRenderer.h>

#include "Renderer.h"

/** Scene renderer */
class SceneRenderer : protected Renderer
{
public:
  /** Create scene renderer */
  SceneRenderer();

  /** Render scene */
  void render(const Scene &scene, RenderContext &renderContext);

private:
  std::unique_ptr<ParticleRenderer> particleRenderer;
  std::unique_ptr<VectorRenderer> vectorRenderer;
  std::unique_ptr<TimeRenderer> timeRenderer;
  std::unique_ptr<AxesRenderer> axesRenderer;
  std::unique_ptr<ColorScaleRenderer> colorScaleRenderer;
  std::map<ContainerShape, ContainerRenderer> containerRenderers;
};

#endif