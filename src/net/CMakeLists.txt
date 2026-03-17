# ====================
# This CMakeLists.txt is under .\src\net\
# ====================

set(NET_FILES
    NetworkDrive.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${NET_FILES}
)