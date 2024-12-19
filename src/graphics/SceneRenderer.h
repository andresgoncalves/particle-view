#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include "Renderer.h"
#include "ParticleRenderer.h"
#include "../models/Scene.h"
#include "../controllers/RenderController.h"

class SceneRenderer : public Renderer<Scene>
{
public:
  SceneRenderer();

  void render(Scene &scene, RenderController &renderController) override;

private:
  std::unique_ptr<ParticleRenderer> particleRenderer;
};

#endif