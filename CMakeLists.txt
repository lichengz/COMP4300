cmake_minimum_required(VERSION 3.16)
project(COMP4300 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(main src/main.cpp
        src/Entity.h
        src/Entity.cpp
        src/Components.h
        src/EntityManager.cpp
        src/EntityManager.h
        src/Vec2.cpp
        src/Vec2.h
        src/GameEngine.cpp
        src/GameEngine.h
        src/GameSettings.h
        src/GameSettings.cpp
        src/GuiManager.cpp
        src/GuiManager.h
        src/ShapeProperties.h
        src/GameSettings.cpp
        src/Utilities.cpp
        src/Utilities.h
        src/Action.cpp
        src/Action.h
        src/Animation.cpp
        src/Animation.h
        src/Scene.cpp
        src/Scene.h
        src/Assets.cpp
        src/Assets.h
        src/MenuScene.cpp
        src/MenuScene.h
        src/GameScene.cpp
        src/GameScene.h
        src/GameSceneSettings.h
        src/Player.cpp
        src/Player.h
        src/Components.cpp
)
target_link_libraries(main PRIVATE sfml-graphics ImGui-SFML::ImGui-SFML)
target_compile_features(main PRIVATE cxx_std_23)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
