cmake_minimum_required(VERSION 3.14)
project(typespeed C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
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
    ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(${TEST_EXECUTABLE} PRIVATE -Wall -Wextra -g -fsanitize=address)
target_link_options(${TEST_EXECUTABLE} PRIVATE -Wall -Wextra -g -fsanitize=address)
add_test(NAME test_c COMMAND ${TEST_EXECUTABLE})
