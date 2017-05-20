cmake_minimum_required(VERSION 3.2)

project (RayTracer)

# externals
include_directories(glm)

add_executable(raytracer main.cpp ray.cpp)
set_target_properties(raytracer PROPERTIES COMPILE_FLAGS "-std=c++14")
