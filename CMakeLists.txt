cmake_minimum_required(VERSION 3.16)

project(
    AutoQuick
    VERSION 1.0.0 
    LANGUAGES CXX
)

add_definitions(-DAPP_VERSION="1.0.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

install(TARGETS AutoQuick
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

enable_testing()