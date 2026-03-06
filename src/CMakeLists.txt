set(SRC_FILES
    main.cpp
    Arguments.cpp
    QuickAccess.cpp
    TimeTable.cpp
    Config.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Shell32
        Ole32
)