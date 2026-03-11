set(SRC_FILES
    main.cpp
    Arguments.cpp
    QuickAccess.cpp
    DataManager.cpp
    NetworkDrive.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

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