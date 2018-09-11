cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Enable test (depends on googletest)." OFF)
option(BUILD_VALGRIND "Enable valgrind (depends on BUILD_TESTING)." OFF)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

add_library(fingera_header
  src/dummy.c
)

target_link_libraries(fingera_header)
target_include_directories(fingera_header
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${BUILD_TESTING} STREQUAL "ON")
  set(BUILD_GMOCK OFF)
  set(INSTALL_GTEST OFF)
  set(gtest_disable_pthreads ON)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(external/googletest)
# 1.7  target_include_directories(gtest PUBLIC ${gtest_SOURCE_DIR}/include)
  include(CTest)
  add_subdirectory(tests)
endif()
