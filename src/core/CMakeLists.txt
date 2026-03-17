# ====================
# This CMakeLists.txt is under .\src\core\
# ====================

set(CORE_FILES
    Arguments.cpp
    DataManager.cpp
    QuickAccess.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CORE_FILES}
)