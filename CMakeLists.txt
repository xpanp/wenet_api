cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(api_main)

# SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

option(TORCH "whether to build with Torch" OFF)
option(ONNX "whether to build with ONNX" ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -fPIC")

set(CMAKE_VERBOSE_MAKEFILE OFF)

include(FetchContent)
include(ExternalProject)
set(FETCHCONTENT_QUIET OFF)
get_filename_component(fc_base "fc_base" REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(FETCHCONTENT_BASE_DIR ${fc_base})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(gflags)
include(glog)  

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/include)
if(TORCH)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/torch_lib)
endif()
if(ONNX)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/onnx_lib)
endif()

add_executable(api_main main.cpp)
target_link_libraries(api_main PUBLIC wenet_api)
target_link_libraries(api_main PUBLIC gflags)
target_link_libraries(api_main PUBLIC glog)
