cmake_minimum_required(VERSION 3.11-3.18)
project(day2)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(day2 main.cpp GameValidator.cpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR})

target_compile_features(day2 PUBLIC cxx_std_20)

enable_testing()

add_executable(main_test test/main_test.cpp)
target_link_libraries(main_test GTest::gtest_main)

# Simple naive test: it runs main and checks return code.
add_test(NAME day2 COMMAND day2)

# Google tests
include(GoogleTest)
gtest_discover_tests(main_test)
