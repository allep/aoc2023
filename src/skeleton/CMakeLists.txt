# Main reference for this CMakeLists.txt:
# https://computingonplains.wordpress.com/building-c-applications-with-cmake-and-visual-studio-code/
#
# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
        Day
	VERSION 0.0.1
        DESCRIPTION "Skeleton for cmake projects")

# On Windows we need to set the following environment variables to make
# this working:
# - GTEST_INCLUDE_DIR
# - GTEST_LIBRARY
# - GTEST_MAIN_LIBRARY
# - GTEST_ROOT
find_package(GTest REQUIRED)

include(CTest)

add_subdirectory(src)
