find_package(Qt6 REQUIRED COMPONENTS
  Gui
  Widgets
  OpenGLWidgets
)

add_library(widgets STATIC
  AppWidget.cpp
  AppWindow.cpp
  GraphicsWidget.cpp
  TimeSliderWidget.cpp
  utils/KeyEventFilter.cpp

  controls/SceneControlPanel.cpp
  controls/ControlSection.cpp
  controls/NumericControl.cpp
  controls/ToolControls.cpp

  controls/ViewControls.cpp
  controls/ViewOriginControls.cpp
  controls/ViewTranslationControls.cpp
  controls/ViewRotationControls.cpp
  controls/ViewScaleControls.cpp

  controls/AnimationControls.cpp
  controls/AnimationTimeControls.cpp
  controls/AnimationSpeedControls.cpp
  controls/AnimationStrategyControls.cpp
)

target_link_libraries(widgets PRIVATE
  Qt6::Gui
  Qt6::Widgets
  Qt6::OpenGLWidgets
)