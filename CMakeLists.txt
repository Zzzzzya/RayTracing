cmake_minimum_required(VERSION 3.20)
project(RayTracingCode)

# packages
find_package(fmt CONFIG REQUIRED)

# include && src
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cc)

message(${SRC_LIST})

# exe
add_executable(RayTracing ${SRC_LIST})

target_link_libraries(RayTracing PRIVATE fmt::fmt)