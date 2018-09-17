


if (${BUILD_TESTING} STREQUAL "ON")
  set(BUILD_GMOCK OFF)
  set(INSTALL_GTEST OFF)
  set(gtest_disable_pthreads ON)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(googletest)
endif()
