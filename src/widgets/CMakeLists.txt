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

  controls/ControlSection.cpp
  controls/NumericControl.cpp

  controls/SceneControlPanel.cpp
  controls/DisplayControlPanel.cpp

  controls/ToolControls.cpp

  controls/view/ViewControls.cpp
  controls/view/ViewOriginControls.cpp
  controls/view/ViewTranslationControls.cpp
  controls/view/ViewRotationControls.cpp
  controls/view/ViewScaleControls.cpp

  controls/animation/AnimationControls.cpp
  controls/animation/AnimationTimeControls.cpp
  controls/animation/AnimationSpeedControls.cpp
  controls/animation/AnimationStrategyControls.cpp

  controls/display/DisplayControls.cpp
  controls/display/DisplayRuleControls.cpp
  controls/display/DisplayRuleGrid.cpp
  controls/display/DisplayRuleRow.cpp

  loader/StoryLoaderDialog.cpp
  loader/StoryLoaderPropertyGrid.cpp
  loader/StoryLoaderPropertyRow.cpp
  loader/StoryLoaderScalarPropertyRow.cpp
  loader/StoryLoaderVectorPropertyRow.cpp
  loader/StoryLoaderAddPropertyDialog.cpp
)

target_link_libraries(widgets PRIVATE
  Qt6::Gui
  Qt6::Widgets
  Qt6::OpenGLWidgets
)