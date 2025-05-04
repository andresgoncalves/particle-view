#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H

#include "Renderer.h"
#include "../models/Scene.h"
#include "../controllers/ViewController.h"

class SceneRenderer : public Renderer<Scene>
{
public:
  SceneRenderer();

  void render(const Scene &scene, const AppContext &appContext) override;

private:
  std::unique_ptr<Renderer<Particle>> particleRenderer;
  std::unique_ptr<Renderer<Particle>> velocityRenderer;
};

#endif