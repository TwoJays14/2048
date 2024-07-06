cmake_minimum_required(VERSION 3.28)
project(2048 C)

set(CMAKE_C_STANDARD 17)

include(FetchContent)

# Fetch raylib (if needed)
set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
FetchContent_MakeAvailable(raylib)

# Fetch raygui (assuming it's header-only)
set(RAYGUI_VERSION 4.0)
FetchContent_Declare(
        raygui
        URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raygui)


add_executable(2048 main.c)

# Include raylib headers
target_include_directories(2048 PRIVATE ${raylib_SOURCE_DIR}/src)

# Include raygui headers
target_include_directories(2048 PRIVATE ${raygui_SOURCE_DIR}/src)

# Link raylib library
target_link_libraries(2048 PRIVATE raylib)

# Link external libraries (as needed)
if (MINGW)
    target_link_libraries(2048 PRIVATE opengl32 gdi32 winmm)
endif()
