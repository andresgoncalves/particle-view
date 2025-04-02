#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "AnimationController.h"
#include "TransformController.h"
#include "ViewController.h"

struct AppContext
{
  AppContext();

  AnimationController animationController;
  TransformController transformController;
  ViewController viewController;
};

#endif