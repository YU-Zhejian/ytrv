project(
  googletest
  VERSION 1.13.0
)

include("${CMAKE_CURRENT_LIST_DIR}/../libceu/cmake_collections/enable_debug.cmake")

add_compile_definitions(GTEST_HAS_PTHREAD=0)
include_directories("${CMAKE_CURRENT_LIST_DIR}/googlemock/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/googlemock/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/googletest/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/googletest/")

file(GLOB GTEST_SRC "${CMAKE_CURRENT_LIST_DIR}/googletest/src/*.cc")
file(GLOB GMOCK_SRC "${CMAKE_CURRENT_LIST_DIR}/googlemock/src/*.cc")

add_library(gtest_shared SHARED ${GTEST_SRC})
add_library(gtest_static STATIC ${GTEST_SRC})
add_library(gmock_shared SHARED ${GMOCK_SRC})
add_library(gmock_static STATIC ${GMOCK_SRC})


ceu_cm_set_static_target(gmock_static)
ceu_cm_set_static_target(gtest_static)
