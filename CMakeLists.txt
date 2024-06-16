cmake_minimum_required(VERSION 3.20)
project(RayTracingCode)

set(CXX_STANDARD_REQUIRED 20)

# packages
find_package(fmt CONFIG REQUIRED)
find_package(Stb REQUIRED)

# include && src
include_directories(${PROJECT_SOURCE_DIR}/include/Base)
include_directories(${PROJECT_SOURCE_DIR}/include/Object)
include_directories(${PROJECT_SOURCE_DIR}/include/Camera)
include_directories(${PROJECT_SOURCE_DIR}/include/Material)
include_directories(${PROJECT_SOURCE_DIR}/include/BVH)
include_directories(${PROJECT_SOURCE_DIR}/include/Texture)
include_directories(${PROJECT_SOURCE_DIR}/include/PerlinNoise)
file(GLOB SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cc)

message(${SRC_LIST})

# exe
add_executable(RayTracing ${SRC_LIST})

target_link_libraries(RayTracing PRIVATE fmt::fmt)
target_include_directories(RayTracing PRIVATE ${Stb_INCLUDE_DIR})