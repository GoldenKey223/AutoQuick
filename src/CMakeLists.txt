add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# add subdirectories
add_subdirectory(core)
add_subdirectory(net)
add_subdirectory(ui)
add_subdirectory(utils)

if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE "-municode")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE FALSE)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Shell32
        Ole32
        Uuid
        Mpr
)