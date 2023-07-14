project(
    "log.c"
    VERSION 0.1.0
    HOMEPAGE_URL https://github.com/rxi/log.c
    LANGUAGES C
)
include("${CMAKE_CURRENT_LIST_DIR}/../libceu/cmake_collections/enable_debug.cmake")

add_compile_definitions(LOG_USE_COLOR)
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")

add_library(log_c_shared SHARED ${CMAKE_CURRENT_LIST_DIR}/src/log.c)
add_library(log_c_static STATIC ${CMAKE_CURRENT_LIST_DIR}/src/log.c)

ceu_cm_set_static_target(log_c_static)
