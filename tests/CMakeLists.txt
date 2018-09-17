
add_executable( test_fingera_header
  test_header.cpp
  test_reflect.cpp
)

target_link_libraries( test_fingera_header fingera_header gtest_main )
add_test(NAME test_fingera_header COMMAND test_fingera_header)

if (${BUILD_VALGRIND} STREQUAL "ON")
  find_program(VALGRIND "valgrind")
  if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full --track-fds=yes $<TARGET_FILE:test_fingera_header>)
  endif()
endif()
