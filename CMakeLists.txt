cmake_minimum_required(VERSION 3.10)
project(osj-gen)

set(CMAKE_CXX_STANDARD 20)
set(SRC hill_mesh.cpp hill_xml.cpp hill.cpp mesh.cpp osj_math.cpp hills_map.cpp)

add_library(pugixml STATIC pugi/pugixml.cpp)
add_library(${PROJECT_NAME}-lib ${SRC})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} pugixml ${PROJECT_NAME}-lib)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Weffc++)