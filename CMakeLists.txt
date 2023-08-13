cmake_minimum_required (VERSION 3.8)

project ("ytrv_all" LANGUAGES C CXX)

# Include sub-projects.
add_subdirectory ("deps/libceu")
include("deps/libceu/cmake/libceu.cmake")

add_subdirectory("deps/log.c")
include_directories("deps/log.c/src")


add_subdirectory ("ytrv")
include("ytrv/cmake/ytrv.cmake")

if(CEU_CM_SHOULD_ENABLE_TEST)
    enable_testing()
    add_subdirectory("deps/labw_gtest")
    include("deps/labw_gtest/gtest.cmake")
    add_subdirectory ("ytrv_test")
endif()
