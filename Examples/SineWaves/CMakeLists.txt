set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (SineWaves Data.cpp MyDistribution.cpp MyModel.cpp main.cpp)
set_target_properties (SineWaves PROPERTIES OUTPUT_NAME main)
target_link_libraries (SineWaves rjobject ${RJOBJ_DEPS})
