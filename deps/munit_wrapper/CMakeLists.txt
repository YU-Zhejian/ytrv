add_library(munit_shared SHARED ../munit/munit.c ../munit/munit.h)
add_library(munit_static STATIC ../munit/munit.c ../munit/munit.h)

set_static_cmake(munit_static)
