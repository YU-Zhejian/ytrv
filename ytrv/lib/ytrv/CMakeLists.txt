file(
        GLOB YTRV_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*/*.c
)

if (YTRV_BUILD_SHARED)
    add_library(${YTRV_LIBRARY_SHARED} SHARED ${YTRV_SOURCES})
    target_link_libraries(${YTRV_LIBRARY_SHARED} INTERFACE "${CEU_LIBRARY_SHARED}" log_c_shared)
endif ()

if (YTRV_BUILD_STATIC)
    add_library(${YTRV_LIBRARY_STATIC} STATIC ${YTRV_SOURCES})
    target_link_libraries(${YTRV_LIBRARY_STATIC} INTERFACE "${CEU_LIBRARY_STATIC}" log_c_static)
    ceu_cm_set_static_target(${YTRV_LIBRARY_STATIC})
endif ()
