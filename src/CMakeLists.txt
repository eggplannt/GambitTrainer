project(src)


set(SOURCES 
    Board.cpp
    main.cpp
    Piece.cpp
    vendor/imgui/imgui_impl_sdl3.cpp 
    vendor/imgui/imgui_impl_sdlrenderer3.cpp
)
message(${SOURCES})

add_executable(trainer ${SOURCES})
target_include_directories(trainer PRIVATE
    vendor/imgui
)
set_target_properties(trainer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_compile_definitions(trainer PUBLIC
      $<$<CONFIG:Debug>:_DEBUG>
      $<$<CONFIG:RelWithDebInfo>:_DEBUG>
      $<$<CONFIG:Release>:_RELEASE>
      $<$<CONFIG:MinSizeRel>:_RELEASE>
)