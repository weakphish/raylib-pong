cmake_minimum_required(VERSION 3.25)
project(raylib_pong)

set(CMAKE_CXX_STANDARD 14)

add_executable(raylib_pong
        main.c)

target_include_directories(raylib_pong PUBLIC /opt/homebrew/Cellar/raylib/4.5.0/include)
find_library(RAYLIB raylib /opt/homebrew/Cellar/raylib/4.5.0/lib)
target_link_libraries(raylib_pong LINK_PUBLIC ${RAYLIB})
