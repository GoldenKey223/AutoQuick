cmake_minimum_required(VERSION 3.16)

project(AutoQuick VERSION 2.0.0 LANGUAGES CXX)

add_definitions(-DAPP_VERSION="2.0.0")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    RESOURCE_PREFIX /
    QML_FILES
        assets/qml/main.qml
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

if (MSVC)
    target_sources(${PROJECT_NAME} PRIVATE qt6.natvis)
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

qt_generate_deploy_qml_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
)

install(SCRIPT ${deploy_script})