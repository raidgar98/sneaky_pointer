cmake_minimum_required(VERSION 3.1)
project(sneaky_pointer CXX)

add_library( sneaky_pointer src/sneaky_pointer.cpp )
target_include_directories( sneaky_pointer PUBLIC include ) #/sneaky_pointer.hpp

# Example usage
add_executable( sample_usage main.cpp )
target_link_libraries( sample_usage sneaky_pointer )

# Tests
find_package(Boost 1.70 REQUIRED COMPONENTS unit_test_framework )
add_executable( sneaky_pointer_tests tests/sneaky_pointer_tests.cpp )
target_include_directories( sneaky_pointer_tests PRIVATE ${Boost_INCLUDE_DIRS} )
target_link_libraries( sneaky_pointer_tests sneaky_pointer ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
add_test( NAME sneaky_pointer_test_all COMMAND sneaky_pointer_tests )
