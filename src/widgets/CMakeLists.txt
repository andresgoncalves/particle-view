find_package(Qt6 REQUIRED COMPONENTS
  Gui
  Widgets
  OpenGLWidgets
)

add_library(widgets STATIC
  AppWidget.cpp
  AppWindow.cpp
  GraphicsWidget.cpp
)

target_link_libraries(widgets PRIVATE
  Qt6::Gui
  Qt6::Widgets
  Qt6::OpenGLWidgets
)