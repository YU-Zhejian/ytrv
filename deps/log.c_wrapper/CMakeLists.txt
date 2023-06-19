add_compile_definitions(LOG_USE_COLOR)
add_library(log_c_shared SHARED ../log.c/src/log.c ../log.c/src/log.h)
add_library(log_c_static STATIC ../log.c/src/log.c ../log.c/src/log.h)

set_static_cmake(log_c_static)
