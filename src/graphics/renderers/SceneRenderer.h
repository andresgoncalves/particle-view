#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include <models/Scene.h>
#include <controllers/ViewController.h>
#include <controllers/ViewController.h>
#include <graphics/renderers/ParticleRenderer.h>
#include <graphics/renderers/VectorRenderer.h>

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
};

#endif