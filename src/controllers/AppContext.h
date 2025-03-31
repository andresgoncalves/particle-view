#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include "StoryController.h"
#include "TransformController.h"
#include "ViewController.h"

struct AppContext
{
  AppContext();

  StoryController storyController;
  TransformController transformController;
  ViewController viewController;
};

#endif