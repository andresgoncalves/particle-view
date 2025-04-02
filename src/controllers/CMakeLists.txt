find_package(Qt6 REQUIRED COMPONENTS
  Gui
)

add_library(controllers STATIC
  AppContext.cpp
  ViewController.cpp
  AnimationController.cpp
  TransformController.cpp
  animation/StepAnimationStrategy.cpp
  animation/LinearAnimationStrategy.cpp
)

target_link_libraries(controllers PRIVATE
  Qt6::Gui
)