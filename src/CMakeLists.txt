project(src)


set(SOURCES 
    Board.cpp
    main.cpp
    Piece.cpp
)

add_executable(trainer ${SOURCES})
set_target_properties(trainer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_compile_definitions(trainer PUBLIC
      $<$<CONFIG:Debug>:_DEBUG>
      $<$<CONFIG:RelWithDebInfo>:_DEBUG>
      $<$<CONFIG:Release>:_RELEASE>
      $<$<CONFIG:MinSizeRel>:_RELEASE>
)