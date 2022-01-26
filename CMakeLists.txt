cmake_minimum_required(VERSION 3.21)
project(sorting_visualizer)
set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR ${PROJECT_SOURCE_DIR}/vendor/SDL2)
find_package(SDL2 REQUIRED)

include_directories(SDL2 ${SDL2_INCLUDE_DIRS})

set(HEADER_FILES
        src/Application.h
        src/Utils.h
        src/Structs.h
        src/Sort.h
        src/Renderer.h
        src/Timer.h
        )
set(SOURCE_FILES
        src/main.cpp
        src/Application.cpp
        src/Sort.cpp
        src/Renderer.cpp
        src/Timer.cpp
        ${HEADER_FILES}
        )

add_executable(sorting_visualizer ${SOURCE_FILES})
target_link_libraries(sorting_visualizer ${SDL2_LIBRARIES})

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    add_custom_command(TARGET sorting_visualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/libs/x64/SDL2.dll"
            "${PROJECT_SOURCE_DIR}/libs/x64/SDL2_ttf.dll"
            "${PROJECT_SOURCE_DIR}/fonts/Roboto-Regular.ttf"
            $<TARGET_FILE_DIR:sorting_visualizer>)
else ()
    add_custom_command(TARGET sorting_visualizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/libs/x86/SDL2.dll"
            "${PROJECT_SOURCE_DIR}/libs/x86/SDL2_ttf.dll"
            "${PROJECT_SOURCE_DIR}/fonts/Roboto-Regular.ttf"
            $<TARGET_FILE_DIR:sorting_visualizer>)
endif ()
