set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
add_executable (Mixture Data.cpp MyDistribution.cpp MyModel.cpp main.cpp)
set_target_properties (Mixture PROPERTIES OUTPUT_NAME main)
target_link_libraries (Mixture rjobject ${RJOBJ_DEPS})
