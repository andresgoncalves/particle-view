find_package(Qt6 REQUIRED COMPONENTS
  Gui
  Widgets
  OpenGLWidgets
)

add_library(widgets STATIC
  app/AppWindow.cpp
  
  app/layout/CenterPanel.cpp
  app/layout/LeftPanel.cpp
  app/layout/RightPanel.cpp
  app/layout/BottomPanel.cpp
  app/layout/MenuBar.cpp
  app/layout/ToolBar.cpp
  app/layout/StatusBar.cpp

  app/tabs/ViewTab.cpp
  app/tabs/AnimationTab.cpp
  app/tabs/DisplayTab.cpp

  app/scene/SceneWidget.cpp

  app/transform/TransformControls.cpp

  app/view/ViewOriginControls.cpp
  app/view/ViewTranslationControls.cpp
  app/view/ViewRotationControls.cpp
  app/view/ViewScaleControls.cpp

  app/animation/AnimationTimeSlider.cpp
  app/animation/AnimationPlayControls.cpp
  app/animation/AnimationTimeControls.cpp
  app/animation/AnimationSpeedControls.cpp
  app/animation/AnimationStrategyControls.cpp

  app/display/DisplayPropertyControls.cpp

  app/color/SolidColorControl.cpp
  app/color/ColorScaleControl.cpp

  app/dialogs/ColorDialog.cpp

  app/storyloader/StoryLoaderDialog.cpp
  app/storyloader/StoryLoaderAddPropertyDialog.cpp
  app/storyloader/StoryLoaderPropertyGrid.cpp
  app/storyloader/StoryLoaderPropertyRow.cpp
  app/storyloader/StoryLoaderScalarPropertyRow.cpp
  app/storyloader/StoryLoaderVectorPropertyRow.cpp
  app/storyloader/StoryLoaderStringPropertyRow.cpp

  app/menu/FileMenu.cpp

  shared/dialogs/ColorPicker.cpp
  shared/buttons/ColorButton.cpp

  shared/sections/Section.cpp

  shared/controls/TextControl.cpp
  shared/controls/ColorControl.cpp
  shared/controls/NumericControl.cpp
  
)

target_link_libraries(widgets PRIVATE
  Qt6::Gui
  Qt6::Widgets
  Qt6::OpenGLWidgets
)