project (RJObject C CXX)
cmake_minimum_required (VERSION 2.8.0)

# Setting this explicitly avoids warnings from versions of CMake >= 3
# regarding policy CMP0042; it should be ignored versions of CMake which don't
# support it. (Setting the policy explicitly will break with old CMakes.)
set (CMAKE_MACOSX_RPATH TRUE)

set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if (CMAKE_COMPILER_IS_GNUCC)
  # if using gcc use gcc-ar and gcc-ranlib rather than ar and ranlib
  set (CMAKE_AR "gcc-ar")
  set (CMAKE_RANLIB "gcc-ranlib")
endif (CMAKE_COMPILER_IS_GNUCC)

set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set (CMAKE_CXX_FLAGS_RELEASE "-m64 -O3 -flto -march=native -funroll-loops")
set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "release")
endif (NOT CMAKE_BUILD_TYPE)

# Initialize the dependencies to an empty list.
set (RJOBJ_DEPS)

# ==========================================================================
#                                                                     DNest3
# ==========================================================================

find_package (DNest3 REQUIRED)
list (APPEND RJOBJ_DEPS ${DNEST3_LIBRARY})
include_directories (SYSTEM ${DNEST3_INCLUDES})

# ==========================================================================
#                                                                        GSL
# ==========================================================================

find_package (GSL REQUIRED)
list (APPEND RJOBJ_DEPS ${GSL_LIBRARIES})
include_directories (SYSTEM ${GSL_INCLUDES})

# ==========================================================================
#                                                                      BOOST
# ==========================================================================

find_package (Boost COMPONENTS thread system REQUIRED)
list (APPEND RJOBJ_DEPS ${Boost_LIBRARIES})
include_directories (SYSTEM ${Boost_INCLUDES})

# ==========================================================================
#                                                                THE LIBRARY
# ==========================================================================

set (RJOBJ_SRC
     Distributions/BasicCircular.cpp
     Distributions/ClassicMassInf.cpp
     Distributions/Distribution.cpp
     Distributions/Pareto.cpp
)

set (RJOBJ_INCLUDES
     Distributions/BasicCircular.h
     Distributions/ClassicMassInf.h
     Distributions/Distribution.h
     Distributions/Pareto.h
     RJObject.h
     RJObjectImpl.h
)

add_library (rjobject ${RJOBJ_SRC})
target_link_libraries (rjobject ${RJOBJ_DEPS})

install (TARGETS rjobject DESTINATION lib)
install (FILES ${RJOBJ_INCLUDES} DESTINATION include/rjobject)

# ==========================================================================
#                                                            DEMO EXECUTABLE
# ==========================================================================

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable (main main.cpp)
target_link_libraries (main rjobject ${RJOBJ_DEPS})

# ==========================================================================
#                                                               THE EXAMPLES
# ==========================================================================

# The examples refer to the headers relative to the project root directory.
include_directories (${PROJECT_SOURCE_DIR})
add_subdirectory (Examples)
