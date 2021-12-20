cmake_minimum_required(VERSION 3.0.0)

project(Chess)

set(CMAKE_CXX_STANDARD 11)

include_directories(
  "include/First\ Layer"
  "include/Second\ Layer"
  "include/Third\ Layer"
)
file(GLOB SRC
  "*.cpp"
  "src/First\ Layer/*.cpp"
  "src/Second\ Layer/*.cpp"
  "src/Third\ Layer/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC})