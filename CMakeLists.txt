# CMake file based on:
# https://github.com/SasLuca/raylib-cmake-template
# https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(dictionary_cs163_project)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(FETCHCONTENT_QUIET FALSE)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_VERSION 4.5.0)
set(RAYLIB-CPP_VERSION 4.5.1)
set(JSON_NLOHMANN_VERSION 3.11.2)

# Setting libraries

# Raylib
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
   include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG ${RAYLIB_VERSION}
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v${RAYLIB-CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# JSON by Nlohmann (https://github.com/nlohmann/json)
find_package(json_nlohmann QUIET)
if (NOT json_nlohmann_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        json_nlohmann
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v${JSON_NLOHMANN_VERSION}
    )
    FetchContent_MakeAvailable(json_nlohmann)
endif()


# Defining the source files and includes
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "header/*.hpp")
file(GLOB_RECURSE HEADERS "header/*.h")

# Set the built executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Set the build directory
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

# Adding the source files to the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Adding the include directory
target_include_directories(${PROJECT_NAME} PUBLIC header)

# Adding the libraries
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)

# MacOS jibbirish
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()