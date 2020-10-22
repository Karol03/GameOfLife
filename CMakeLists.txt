cmake_minimum_required(VERSION 3.5)

project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -pedantic -O0 -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


set(SFML_DIR "C:/SFML-2.5.1-mingw/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)
include_directories(GameOfLife "C:/SFML-2.5.1-mingw/include")

add_executable(GameOfLife
        main.cpp

        # headers
        area.hpp
        gameoflife.hpp
        graphics.hpp
        object.hpp
    )

target_link_libraries(GameOfLife sfml-graphics sfml-system)
