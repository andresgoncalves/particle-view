find_package(Qt6 REQUIRED COMPONENTS
  Gui
)

add_library(utils STATIC
  color/SolidColorStrategy.cpp
  color/ColorScaleStrategy.cpp
)

target_link_libraries(utils PRIVATE
  Qt6::Gui
)