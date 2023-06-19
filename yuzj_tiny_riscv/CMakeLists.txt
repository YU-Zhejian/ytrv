include("${CMAKE_CURRENT_LIST_DIR}/cmake/yuzj_tiny_riscv.cmake")

if (${HAVE_WORKING_C_HELLOWORLD_RUN_SHARED} EQUAL 0)
    set(YTRV_BUILD_SHARED TRUE)
    message(STATUS "YTRV: Will build shared ytrv")
else ()
    message(FATAL_ERROR "YTRV: Will NOT build shared ytrv!")
endif ()

if (${HAVE_WORKING_C_HELLOWORLD_RUN_STATIC} EQUAL 0)
    set(YTRV_BUILD_STATIC TRUE)
    message(STATUS "YTRV: Will build static ytrv")
else ()
    message(STATUS "YTRV: Will NOT build static ytrv")
endif ()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/lib")
add_executable (yuzj_tiny_riscv "main.c")
target_link_libraries (yuzj_tiny_riscv "${CEU_LIBRARY_STATIC}" "${YTRV_LIBRARY_STATIC}")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test")
