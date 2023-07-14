# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("ytrv_all" LANGUAGES C CXX)

# Include sub-projects.
add_subdirectory ("deps/libceu")
include("deps/libceu/cmake/libceu.cmake")
include("deps/libceu/cmake_collections/find_or_get_gtest.cmake")

ceu_cm_find_or_get_gtest(
	POLICY "Download"
	GIT_REPOSITORY "http://localhost:3000/app_mirror/googletest"
)

# add_subdirectory("deps/munit_wrapper")
# include_directories("deps/munit")

# add_subdirectory("deps/log.c_wrapper")
# include_directories("deps/log.c/src")

# add_subdirectory("deps/doctest")
# include_directories("deps/doctest/doctest")

# add_subdirectory ("ytrv")
# include_directories("ytrv/include")
# add_subdirectory ("ytrv_test")
