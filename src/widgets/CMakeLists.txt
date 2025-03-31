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
)

target_link_libraries(widgets PRIVATE
  Qt6::Gui
  Qt6::Widgets
  Qt6::OpenGLWidgets
)