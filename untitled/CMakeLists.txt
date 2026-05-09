cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled src/main.cpp
        src/solicitud.hpp
        src/parser.cpp
        src/parser.hpp
        src/mergesort.cpp
        src/busqueda.hpp
        src/busqueda.cpp
        src/grafo.cpp
        src/unionfind.hpp
        src/mochila.hpp
        src/mochila.cpp
)
