cmake_minimum_required(VERSION 3.28)
project(GraphicsForUIProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BUILD_SHARED_LIBS OFF)
add_definitions(-DSFML_STATIC)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

set(SFML_USE_STATIC_STD_LIBS TRUE CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SFML)

add_subdirectory(src)

add_subdirectory(examples)