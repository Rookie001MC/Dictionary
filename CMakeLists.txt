# CMake file based on:
# https://github.com/SasLuca/raylib-cmake-template
# https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
SET(MSVC_INCREMENTAL_DEFAULT ON)
project(cs163_project)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(FETCHCONTENT_QUIET FALSE)

set(CMAKE_CXX_STANDARD 20)

# Setting libraries

# Raylib
set(RAYLIB_VERSION 4.5.0)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# RayGUI
set(RAYGUI_VERSION 3.6)
find_package(raygui ${RAYGUI_VERSION} QUIET)
if (NOT raygui_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raygui
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raygui)
  if (NOT raygui_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raygui)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})
  endif()
endif()

# Boost
option(BOOST_DISABLE_TESTS "Disable Boost tests" OFF)
set(BOOST_VERSION 1.82.0)

find_package(Boost ${BOOST_VERSION})
if (NOT Boost_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    Boost
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    DOWNLOAD_NO_EXTRACT FALSE
    URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}.tar.gz
  )
  # set(BOOST_INCLUDE_LIBRARIES timer filesystem regex)
  FetchContent_MakeAvailable(boost)
  set(BOOST_ENABLE_CMAKE ON)
endif()

# Defining the source files and includes
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.hpp include/*.h")

# Set the built executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Set the build directory
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)

# Adding the source files to the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Adding the include directory
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Adding the libraries
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raygui)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem Boost::serialization)

# MacOS jibbirish
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL")
endif()