#include "AppContext.h"

AppContext::AppContext() : transformController{viewController}
{
  animationController.storyObservable.subscribe(this,
                                                [this]()
                                                {
                                                  auto story = animationController.getStory();
                                                  animationController.setAnimationSpeed(6.0 * (story.metadata.endTime - story.metadata.startTime) / story.scenes.size());
                                                  animationController.reset();
                                                  viewController.setOrigin(story.getOrigin());
                                                  viewController.setBaseScale(story.getBaseScale());
                                                  viewController.setRotation({});
                                                  viewController.setTranslation({});
                                                  viewController.setScale(1.0f);
                                                  displayController.clearCustomRules();
                                                  graphController.clearGraphs();
                                                });
}
AppContext::~AppContext()
{
  animationController.storyObservable.unsubscribe(this);
}