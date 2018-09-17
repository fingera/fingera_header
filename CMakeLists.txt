cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Enable test (depends on googletest)." OFF)
option(BUILD_EXTERNAL "Enable external modules" ON)
option(BUILD_VALGRIND "Enable valgrind (depends on BUILD_TESTING)." OFF)

if (${BUILD_EXTERNAL} STREQUAL "ON")
  add_subdirectory(external)
endif()

add_library(fingera_header
  src/dummy.c
)

target_link_libraries(fingera_header)
target_include_directories(fingera_header
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${BUILD_TESTING} STREQUAL "ON")
  include(CTest)
  add_subdirectory(tests)
endif()
