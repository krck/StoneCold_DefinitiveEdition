cmake_minimum_required(VERSION 3.20)

# Set Compiler and C++ language 
set(CMAKE_CXX_STANDARD 17)
add_compile_options(
  "-Wall" "-Wpedantic" "-Wextra" "-fexceptions"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

# Define Project Name (${PROJECT_NAME} variable)
project(stone_cold)

# Output all exe and .a (libs) to /bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/bin)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}  src/Application.cpp
                                src/StoneCold.Assets/AssetManager.cpp
                                src/StoneCold.Core/Exception.cpp
                                src/StoneCold.Core/GameCore.cpp
                                src/StoneCold.Core/MapManager.cpp
                                src/StoneCold.Core/SfmlManager.cpp
                                src/StoneCold.ECS/EntityComponentSystem.cpp
                                src/StoneCold.GUI/Button.cpp
                                src/StoneCold.Scenes/MainMenuScene.cpp
                                src/StoneCold.Scenes/GamePlayScene.cpp)
add_subdirectory(external/sfml)

# Link library/additional include paths
target_include_directories(${PROJECT_NAME}  PUBLIC external/sfml/include
                                            PUBLIC external/nlohmann_json
                                            PUBLIC external/SSARCandy_ini
                                            PUBLIC src/StoneCold.Assets
                                            PUBLIC src/StoneCold.Core
                                            PUBLIC src/StoneCold.ECS
                                            PUBLIC src/StoneCold.GUI
                                            PUBLIC src/StoneCold.Scenes)
# Link library/additional source paths
target_link_directories(${PROJECT_NAME} PRIVATE external/sfml/src)
# Link compiled/binary libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

# Copy config files to the /bin
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/sc_assets.json ${CMAKE_BINARY_DIR}/x64/bin/config/sc_assets.json COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/sc_sprites.json ${CMAKE_BINARY_DIR}/x64/bin/config/sc_sprites.json COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config/sc_settings.json ${CMAKE_BINARY_DIR}/x64/bin/config/sc_settings.json COPYONLY)
# Copy asset files to the /bin
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/player/Dwarf_Sprite.png ${CMAKE_BINARY_DIR}/x64/bin/assets/player/Dwarf_Sprite.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/monsters/Skeleton.png ${CMAKE_BINARY_DIR}/x64/bin/assets/monsters/Skeleton.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/map/grasslands.png ${CMAKE_BINARY_DIR}/x64/bin/assets/map/grasslands.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/ui/gui_button.png ${CMAKE_BINARY_DIR}/x64/bin/assets/ui/gui_button.png COPYONLY)
# Copy font files to the /bin
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/Crom.ttf ${CMAKE_BINARY_DIR}/x64/bin/assets/fonts/Crom.ttf COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/OldeDethek.ttf ${CMAKE_BINARY_DIR}/x64/bin/assets/fonts/OldeDethek.ttf COPYONLY)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /x64/bin)
