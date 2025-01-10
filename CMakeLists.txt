string(REPLACE "\\" "/" VCPKG_PATH $ENV{VCPKG_ROOT})
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_INSTALLED_DIR ${CMAKE_SOURCE_DIR}/vcpkg_installed)


cmake_minimum_required(VERSION 3.29)
project(GambitTrainer VERSION 1.0)


find_package(SDL3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(src)

target_link_libraries(trainer PRIVATE imgui::imgui SDL3::SDL3 fmt::fmt)
