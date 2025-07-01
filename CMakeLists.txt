cmake_minimum_required(VERSION 3.16)

set(fltk_DIR "C:/Users/20690/vcpkg/installed/x64-windows/share/fltk")

project(Plane)

find_package(fltk CONFIG REQUIRED)

add_subdirectory(code code)
