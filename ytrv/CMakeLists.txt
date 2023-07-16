project("ytrv" LANGUAGES C)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/ytrv.cmake")

if (${CEU_CM_HAVE_WORKING_C_HELLOWORLD_RUN_SHARED} EQUAL 0)
    set(YTRV_BUILD_SHARED TRUE CACHE BOOL "")
    message(STATUS "${PROJECT_NAME}: Will build shared ${PROJECT_NAME}")
else ()
    set(YTRV_BUILD_SHARED FALSE CACHE BOOL "")
    message(STATUS "${PROJECT_NAME}: Will NOT build shared ${PROJECT_NAME}!")
endif ()

if (${CEU_CM_HAVE_WORKING_C_HELLOWORLD_RUN_STATIC} EQUAL 0)
    set(YTRV_BUILD_STATIC TRUE CACHE BOOL "")
    message(STATUS "${PROJECT_NAME}: Will build static ${PROJECT_NAME}")
else ()
    set(YTRV_BUILD_STATIC FALSE CACHE BOOL "")
    message(STATUS "${PROJECT_NAME}: Will NOT build static ${PROJECT_NAME}")
endif ()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/lib")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/bin")
