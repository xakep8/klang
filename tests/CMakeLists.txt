add_executable(klang_tests smoke_tests.cpp)

target_link_libraries(klang_tests PRIVATE klang_core)

add_test(NAME klang_tests COMMAND klang_tests)
