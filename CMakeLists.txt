cmake_minimum_required(VERSION 3.29)
project(GambitTrainer VERSION 1.0)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_SCAN_FOR_MODULES 0)



find_package(SDL3 CONFIG REQUIRED)

add_executable(trainer src/main.cpp)
target_link_libraries(trainer PRIVATE SDL3::SDL3)
set_target_properties(trainer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_compile_definitions(trainer PUBLIC
      $<$<CONFIG:Debug>:_DEBUG>
      $<$<CONFIG:RelWithDebInfo>:_DEBUG>
      $<$<CONFIG:Release>:_RELEASE>
      $<$<CONFIG:MinSizeRel>:_RELEASE>
)