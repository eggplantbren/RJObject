set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (GalaxyField Data.cpp MyDistribution.cpp MyModel.cpp main.cpp)
set_target_properties (GalaxyField PROPERTIES OUTPUT_NAME main)
target_link_libraries (GalaxyField rjobject ${RJOBJ_DEPS})
