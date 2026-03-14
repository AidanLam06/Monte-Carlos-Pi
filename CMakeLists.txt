cmake_minimum_required(VERSION 3.10)
project(pi_estimator_MC LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files here
add_executable(pi_estimator_MC src/main.cpp src/Dot.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)