cmake_minimum_required(VERSION 3.2)

project (RayTracer)

# externals
include_directories(glm)

add_executable(raytracer main.cpp ray.cpp hitable.cpp sphere.cpp hitablelist.cpp camera.cpp material.cpp) 
set_target_properties(raytracer PROPERTIES COMPILE_FLAGS "-std=c++14")
