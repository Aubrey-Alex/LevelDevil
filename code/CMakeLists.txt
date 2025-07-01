add_library(precompiled INTERFACE)
target_precompile_headers(precompiled INTERFACE precomp.h)

find_package(FLTK CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    App/App.cpp
    App/App.h
    common/commands.h
    common/Entity.h
    common/frame.cpp
    common/frame.h
    common/game_map.h
    common/property_ids.h
    common/globals.cpp
    Model/entity_model.h
    Model/object.h
    View/MainWindow.cpp
    View/MainWindow.h
    View/widgets/GameWidget.cpp
    View/widgets/GameWidget.h
    ViewModel/entity_view_model.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fltk
    fltk_forms
    fltk_images
    nlohmann_json::nlohmann_json
    precompiled
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/level1.json
    ${CMAKE_CURRENT_BINARY_DIR}/level1.json
    COPYONLY
)