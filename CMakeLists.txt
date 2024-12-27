cmake_minimum_required(VERSION 3.14)
project(typespeed C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCES
  src/typespeed.c
  src/dict.c
  src/scene.c
  src/util.c
  src/memory/arena.c
  src/assets.c
  src/memory/slab.c
  src/scenes/gameplay.c
  src/scenes/main.c
  src/components/title.c
  src/components/play_button.c
  src/components/player_input.c
  src/components/word.c
)
add_executable(${PROJECT_NAME} ${SOURCES})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/scenes
    ${CMAKE_SOURCE_DIR}/src/components
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a
)
if(APPLE)
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      "-framework IOKit"
      "-framework Cocoa"
      "-framework OpenGL"
  )
endif()

set(TEST_EXECUTABLE tests)
set(TEST_SOURCES
  test/test.c
  test/munit/munit.c
  src/memory/arena.c
)
enable_testing()
add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})
target_include_directories(${TEST_EXECUTABLE}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src/memory
)
target_compile_options(${TEST_EXECUTABLE} PRIVATE -Wall -Wextra -g -fsanitize=address)
target_link_options(${TEST_EXECUTABLE} PRIVATE -Wall -Wextra -g -fsanitize=address)
add_test(NAME test_c COMMAND ${TEST_EXECUTABLE})
