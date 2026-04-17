cmake_minimum_required(VERSION 3.11)
project(OrbitalSimulation)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(OrbitalSim ${SOURCES})

target_link_libraries(OrbitalSim raylib)