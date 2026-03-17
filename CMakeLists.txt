cmake_minimum_required(VERSION 3.16)

project(
    AutoQuick
    VERSION 1.0.0 
    LANGUAGES CXX
)

add_definitions(-DAPP_VERSION="1.1.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install location" FORCE)
endif()

add_subdirectory(src)

install(TARGETS AutoQuick
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

enable_testing()