cmake_minimum_required(VERSION 2.8)

project(SteRoEngine)

set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror=return-type -fopenmp -ffast-math -O3 -g")

include_directories("include")

file(GLOB_RECURSE source_files "main.cpp" "raycast.cpp" "renderer.cpp")
file(GLOB_RECURSE header_files "*.h")

add_executable(${PROJECT_NAME} ${source_files} ${header_files})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
