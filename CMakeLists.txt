cmake_minimum_required(VERSION 3.20)

# Define Project Name (${PROJECT_NAME} variable)
project(stone_cold)

# Output all exe and .a (libs) to /bin
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/bin)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} src/Application.cpp)
add_subdirectory(external/sfml)

# Link library/additional include paths
target_include_directories(${PROJECT_NAME} PUBLIC external/sfml/include)
# Link library/additional source paths
target_link_directories(${PROJECT_NAME} PRIVATE external/sfml/src)
# Link compiled/binary libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /x64/bin)
