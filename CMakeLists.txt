cmake_minimum_required(VERSION 3.1.0)
project(tracer)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/api/cmake)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(api/glfw)

find_package(USD 19.05 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(
    Boost REQUIRED
    COMPONENTS regex system filesystem thread date_time atomic python)
find_package(embree 3.0 REQUIRED)
find_package(TBB REQUIRED)

set(USD_LIBS
    ${USD_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${Boost_ATOMIC_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PYTHON_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -std=c++14")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
    api/embree/include/
    api/glad/include/
    api/glfw/include/
    api/imgui/
    api/stb/
    api/tinyexr/
    src/bsdf/
    src/camera/
    src/gui/
    src/integrator/
    src/material/
    src/math/
    src/object/
    src/opengl/
    src/render/
    src/sampling/
    src/scene/
    src/utility/
    ${USD_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${EMBREE_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS})

file(GLOB API_SOURCES
    api/glad/src/glad.c
    api/imgui/*.cpp)

file(GLOB PROJECT_HEADERS
    src/bsdf/*.h
    src/camera/*.h
    src/gui/*.h
    src/integrator/*.h
    src/material/*.h
    src/math/*.h
    src/object/*.h
    src/opengl/*.h
    src/render/*.h
    src/sampling/*.h
    src/scene/*.h
    src/utility/*.h
    src/*.h)

file(GLOB PROJECT_SOURCES
    src/bsdf/*.cpp
    src/camera/*.cpp
    src/gui/*.cpp
    src/integrator/*.cpp
    src/material/*.cpp
    src/math/*.cpp
    src/object/*.cpp
    src/opengl/*.cpp
    src/render/*.cpp
    src/sampling/*.cpp
    src/scene/*.cpp
    src/utility/*.cpp
    src/*.cpp)

file(GLOB PROJECT_SHADERS
    res/shaders/*.frag
    res/shaders/*.glsl
    res/shaders/*.vert)

file(GLOB PROJECT_SCENES
    res/scenes/*.usd
    res/scenes/*.usda
    res/scenes/*.usdc
    res/scenes/*.usdz)

file(GLOB PROJECT_CONFIGS
    CMakeLists.txt
    README.md
    .gitattributes
    .gitignore
    .gitmodules)

source_group("API" FILES ${API_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Scenes" FILES ${PROJECT_SCENES})

add_definitions(-DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${API_SOURCES}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_SCENES}
    ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME}
    glfw
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    ${USD_LIBS}
    ${EMBREE_LIBRARY}
    ${TBB_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
