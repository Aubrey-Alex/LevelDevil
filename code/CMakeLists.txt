cmake_minimum_required(VERSION 3.15)
project(EntityModelTest LANGUAGES CXX)

# 基础配置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 显式设置FLTK路径（关键修正）
set(FLTK_DIR "C:/Users/20690/vcpkg/installed/x64-windows/share/fltk")
include(${FLTK_DIR}/FLTKConfig.cmake)  # 手动包含配置文件

# 显式设置nlohmann_json路径
set(nlohmann_json_DIR "C:/Users/20690/vcpkg/installed/x64-windows/share/nlohmann_json")
find_package(nlohmann_json CONFIG REQUIRED)
cmake_minimum_required(VERSION 3.15)
project(EntityModelTest LANGUAGES CXX)

# 只编译测试文件
add_executable(entity_model_test 
    common/game_map.h
    common/property_ids.h
    common/entity.h
    Model/entity_model_test.cpp
    Model/entity_model.h
    Model/object.h
)

# 包含路径
target_include_directories(entity_model_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
)

# 处理JSON文件
configure_file(
    Model/level1.json
    ${CMAKE_CURRENT_BINARY_DIR}/level1.json
    COPYONLY
)