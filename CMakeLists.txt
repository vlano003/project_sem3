cmake_minimum_required(VERSION 3.19)
project(project_sem3)

set(CMAKE_CXX_STANDARD 14 )

add_executable(project_sem3 main.cpp
        BombMode.cpp BombMode.h
        Figure.cpp Figure.h
        Game.cpp Game.h
        HardcoreMode.cpp HardcoreMode.h
        Logic.cpp Logic.h
        Render.cpp Render.h
        UI.cpp UI.h)

target_link_libraries(project_sem3 sfml-graphics)

set(SFML_DIR "C:\\Users\\Admin\\CLionProjects\\lib\\sfml\\GCC 7.3.0 MinGW (SEH) - 64-bit\\SFML-2.5.1\\lib\\cmake\\SFML")
find_package(SFML 2.5 REQUIRED graphics network audio window system)