#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "AnimationController.h"
#include "TransformController.h"
#include "ViewController.h"
#include "ContainerController.h"
#include "DisplayController.h"
#include "GraphController.h"

struct AppContext
{
  AppContext();

  AnimationController animationController;
  TransformController transformController;
  ViewController viewController;
  ContainerController containerController;
  DisplayController displayController;
  GraphController graphController;
};

#endif