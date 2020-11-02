cmake_minimum_required(VERSION 3.4)

set(HW_NUMBER 7)
set(IS_CHECKER FALSE)

message("########################################################")
message("                 CS104 HW${HW_NUMBER} Test Suite")
message("########################################################")

project(CS104-HW${HW_NUMBER}-Test-Suite C CXX)

# pick up include files
# ----------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/test_cmake_lib)

include(Policies NO_POLICY_SCOPE)
include(Utils)
include(Shorthand)
include(LibraryUtils)
include(104CompileFlags)
include(TestTargets)

# setup Valgrind
# ----------------------------------------------------------

find_program(VALGRIND NAMES valgrind DOC "Path to valgrind executable")
import_executable(valgrind ${VALGRIND})

set(VALGRIND_ARGS --tool=memcheck 
	--leak-check=yes
	--trace-children=no) # don't valgrind child processes, we control manually which processes are valground

if(IS_CHECKER)
	# if this is a HW checker, make Valgrind errors cause tests to fail 
	list(APPEND VALGRIND_ARGS --error-exitcode=113)
endif()

# find GTest
# ----------------------------------------------------------

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

import_libraries(gtest LIBRARIES ${GTEST_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})
import_libraries(gtest_main LIBRARIES ${GTEST_MAIN_LIBRARIES} INCLUDES ${GTEST_INCLUDE_DIRS})

include(CustomTests)
enable_testing()

# find user code dir
# ----------------------------------------------------------

if(NOT DEFINED HW_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.h" "${CMAKE_BINARY_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw${HW_NUMBER} dir, or run CMake with the \"-DHW_DIR=<path to hw${HW_NUMBER}>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw${HW_NUMBER} assignment directory")
	endif()
endif()

# make sure HW_DIR is an absolute path.
# this will shadow the cache variable with a local variable
get_filename_component(HW_DIR "${HW_DIR}" REALPATH)


# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(bst_tests)
add_subdirectory(avl_tests)
add_subdirectory(sat_tests)

if(NOT IS_CHECKER)
	gen_grade_target()
endif()
