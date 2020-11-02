# File for our test suite target creator functions

# Constants
set(TEST_TIMEOUT 60) # seconds
set(COMPILE_LOG_DIR ${CMAKE_BINARY_DIR}/compile-logs)
set(OUTPUT_LOG_DIR ${CMAKE_BINARY_DIR}/test-output)
file(MAKE_DIRECTORY ${COMPILE_LOG_DIR} ${OUTPUT_LOG_DIR})

# There are essentially four cases for how student code is structured.
# Case 1:
# The student provides one or more .cpp files, which we compile into an executable and then run.
# We save the compile output from their code, not ours.
# Case 2:
# The student provides .cpp and .h files, which we compile and link with, and then run GTest cases on.
# We save the compile output from building our test cases.
# Case 3:
# The student provides a Makefile that compiles their executable when a certain target is built.
# We save the output from Make in this case.
# Case 4:
# The student provides their implementation as only .h files, and we compile against them and
# run GTests on them

# Declare global variables to store 'make grade' command info.

set(MAKE_GRADE_COMMAND_BODY "" CACHE "" INTERNAL FORCE)
set(HAS_ANY_MAKEFILE_PROBLEMS FALSE)


# Function for case 1, where we build the user's executable for them, then execute it
# usage: add_executable_problem(NAME <question name> USER_SOURCE <full path to source files in hw dir> TEST_SOURCE <test source files in current dir, won't be run with Valgrind>)
function(add_executable_problem)
	cmake_parse_arguments(ALS "" "NAME" "USER_SOURCE;TEST_SOURCE" ${ARGN})

	if(NOT ALS_NAME OR NOT ALS_USER_SOURCE OR NOT ALS_TEST_SOURCE)
		message(FATAL_ERROR "Missing arguments!")
	endif()

	# --------------------------------
	# add targets

	# Gracefully handle the case where a source file is missing.
	# It's OK if we get a build error but we need CMake to at least succeed,
	# or the test runner will get in trouble.
	foreach(FILE ${ALS_USER_SOURCE})
		if(NOT EXISTS ${FILE})
			message(WARNING "Source file for problem ${ALS_NAME} could not be found: ${FILE}")
			list(REMOVE_ITEM ALS_USER_SOURCE ${FILE})
		endif()
	endforeach()

	if("${ALS_USER_SOURCE}" STREQUAL "")
		message(WARNING "No user source files exist for ${NAME}, skipping build")
		return()
	endif()

	# build user code
	add_executable(hw${HW_NUMBER}_${ALS_NAME} ${ALS_USER_SOURCE})
	target_include_directories(hw${HW_NUMBER}_${ALS_NAME} PRIVATE ${HW_DIR})

	# build test code
	add_executable(${ALS_NAME}_tests ${ALS_TEST_SOURCE})

	target_link_libraries(${ALS_NAME}_tests gtest gtest_main testing_utils)

	# tell the tests where the executable is through a macro
	string(TOUPPER ${ALS_NAME} NAME_UCASE)
	target_compile_definitions(${ALS_NAME}_tests PUBLIC ${NAME_UCASE}_EXECUTABLE=\"$<TARGET_FILE:hw${HW_NUMBER}_${ALS_NAME}>\")

	# add Google tests
	add_executable_gtests(${ALS_NAME}_tests FALSE FALSE)

	# make sure that user executable gets built when tests are built
	add_dependencies(${ALS_NAME}_tests hw${HW_NUMBER}_${ALS_NAME})

	# --------------------------------
	# append 'make grade' commands

	# build executable
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${ALS_NAME}, output saved to ${COMPILE_LOG_DIR}/${ALS_NAME}.complog" CACHE "" INTERNAL FORCE)
    set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make hw${HW_NUMBER}_${ALS_NAME} 1>${COMPILE_LOG_DIR}/${ALS_NAME}.complog 2>&1 || true CACHE "" INTERNAL FORCE)

    # build tests
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${ALS_NAME} tests" CACHE "" INTERNAL FORCE)
    set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${ALS_NAME}_tests || true CACHE "" INTERNAL FORCE)

endfunction(add_executable_problem)

# Function for case 2, where we build the user's source files for them, then run GTest tests on them
# usage: add_source_problem(NAME <question name> USER_SOURCE <full path to source files in hw dir> TEST_SOURCE <test source files in current dir> RUNTIME_TEST_SOURCE <test source that is not executed in valgrind>)
function(add_source_problem)
	cmake_parse_arguments(ASP "" "NAME" "USER_SOURCE;TEST_SOURCE;RUNTIME_TEST_SOURCE" ${ARGN})

	# --------------------------------
	# add targets

	# Gracefully handle the case where a source file is missing.
	# It's OK if we get a build error but we need CMake to at least succeed,
	# or the test runner will get in trouble.
	foreach(FILE ${ASP_USER_SOURCE})
		if(NOT EXISTS ${FILE})
			message(WARNING "Source file for problem ${ASP_NAME} could not be found: ${FILE}")
			list(REMOVE_ITEM ASP_USER_SOURCE ${FILE})
		endif()
	endforeach()

	if("${ASP_USER_SOURCE}" STREQUAL "")
		message(WARNING "No user source files exist for ${NAME}, skipping build")
		return()
	endif()

	# build user code (as seperate library so that compile errors are only tracked for user code
	add_library(hw${HW_NUMBER}_${ASP_NAME} STATIC ${ASP_USER_SOURCE})
	target_include_directories(hw${HW_NUMBER}_${ASP_NAME} PUBLIC ${HW_DIR})

	# prevent any main() functions in user code from hijacking the test cases
	target_compile_definitions(hw${HW_NUMBER}_${ASP_NAME} PUBLIC main=disabled_main)

	# build test code
	add_executable(${ASP_NAME}_tests ${ASP_TEST_SOURCE})
	target_link_libraries(${ASP_NAME}_tests hw${HW_NUMBER}_${ASP_NAME} gtest gtest_main testing_utils)

	# add Google tests
	add_executable_gtests(${ASP_NAME}_tests TRUE TRUE)

	# also build runtime test code
	if(NOT "${ASP_RUNTIME_TEST_SOURCE}" STREQUAL "")
		add_executable(${ASP_NAME}_runtime_tests ${ASP_RUNTIME_TEST_SOURCE})
		target_link_libraries(${ASP_NAME}_runtime_tests hw${HW_NUMBER}_${ASP_NAME} gtest gtest_main testing_utils)

		add_executable_gtests(${ASP_NAME}_runtime_tests FALSE TRUE)
	endif()

	# --------------------------------
	# append 'make grade' commands

	# build user code
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${ASP_NAME}, output saved to ${COMPILE_LOG_DIR}/${ASP_NAME}.complog" CACHE "" INTERNAL FORCE)
    set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make hw${HW_NUMBER}_${ASP_NAME} 1>${COMPILE_LOG_DIR}/${ASP_NAME}.complog 2>&1 || true CACHE "" INTERNAL FORCE)

    # build tests
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${ASP_NAME} tests" CACHE "" INTERNAL FORCE)
    set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${ASP_NAME}_tests || true CACHE "" INTERNAL FORCE)

	if(NOT "${ASP_RUNTIME_TEST_SOURCE}" STREQUAL "")
		# build runtime tests
		set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${ASP_NAME} runtime tests" CACHE "" INTERNAL FORCE)
		set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${ASP_NAME}_runtime_tests || true CACHE "" INTERNAL FORCE)
	endif()

endfunction(add_source_problem)

# Function for case 3, where we run the user's makefile to generate an executable, then test it with GTest test cases
# If a MAKE_TARGET is not given, then make will be executed with no arguments.
# usage: add_makefile_problem(NAME <question name> [MAKE_TARGET <target>] EXECUTABLE_NAME <name of executable that is made> TEST_SOURCE <test source files in current dir>, won't be run with Valgrind)
function(add_makefile_problem)
	cmake_parse_arguments(AMP "" "NAME;MAKE_TARGET;EXECUTABLE_NAME" "TEST_SOURCE" ${ARGN})

	# check that a Makefile actually exists
	# since Make can do strange stuff due to implicit rules if it's invoked in a a directory without a Makefile
	if(NOT EXISTS "${HW_DIR}/Makefile")
		message(WARNING "Cannot find Makefile in user hw${HW_NUMBER} directory")
	endif()

	# --------------------------------
	# add targets

	set(USER_EXECUTABLE ${HW_DIR}/${AMP_EXECUTABLE_NAME})

	# find all c++ files as dependencies, so that we know to rerun the makefile when the user edits their code
	file(GLOB_RECURSE USER_SOURCE_FILES "${HW_DIR}/*.cpp" "${HW_DIR}/*.h")

	if("${AMP_MAKE_TARGET}" STREQUAL "")
		set(MAKE_COMMENT_MESSAGE "Running 'make' in hw${HW_NUMBER} directory...")
	else()
		set(MAKE_COMMENT_MESSAGE "Running 'make ${AMP_MAKE_TARGET}' in hw${HW_NUMBER} directory...")
	endif()

	add_custom_command(OUTPUT ${USER_EXECUTABLE}
		COMMAND make ${AMP_MAKE_TARGET}
		WORKING_DIRECTORY ${HW_DIR}
		VERBATIM
		DEPENDS ${USER_SOURCE_FILES} ${HW_DIR}/Makefile
		COMMENT "${MAKE_COMMENT_MESSAGE}")

	add_custom_target(run_make_${AMP_NAME}
		ALL
		DEPENDS ${USER_EXECUTABLE})


	# build test code
	add_executable(${AMP_NAME}_tests ${AMP_TEST_SOURCE})
	target_link_libraries(${AMP_NAME}_tests gtest gtest_main testing_utils)

	string(TOUPPER ${AMP_NAME} NAME_UCASE)
	target_compile_definitions(${AMP_NAME}_tests PUBLIC ${NAME_UCASE}_EXECUTABLE=\"${USER_EXECUTABLE}\")

	# add Google tests
	add_executable_gtests(${AMP_NAME}_tests FALSE FALSE)

	# make sure that user executable gets built when tests are built
	add_dependencies(${AMP_NAME}_tests run_make_${AMP_NAME})

	# --------------------------------
	# append 'make grade' commands

	# build executable
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${AMP_NAME} using Makefile, output saved to ${COMPILE_LOG_DIR}/${AMP_NAME}.complog" CACHE "" INTERNAL FORCE)
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make run_make_${AMP_NAME} 1>${COMPILE_LOG_DIR}/${AMP_NAME}.complog 2>&1 || true CACHE "" INTERNAL FORCE)

	# build tests
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${AMP_NAME} tests" CACHE "" INTERNAL FORCE)
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${AMP_NAME}_tests || true CACHE "" INTERNAL FORCE)

endfunction(add_makefile_problem)

# Function for case 4, where we compile GTest tests that include header-only user code.
# usage: add_header_problem(NAME <question name> TEST_SOURCE <test source files in current dir> RUNTIME_TEST_SOURCE <test source that is not executed in valgrind>)
function(add_header_problem)
	cmake_parse_arguments(AHP "" "NAME" "TEST_SOURCE;RUNTIME_TEST_SOURCE" ${ARGN})

	# --------------------------------
	# add targets

	# build test code
	add_executable(${AHP_NAME}_tests ${AHP_TEST_SOURCE})
	target_link_libraries(${AHP_NAME}_tests gtest gtest_main testing_utils)
	target_include_directories(${AHP_NAME}_tests PUBLIC ${HW_DIR})

	# prevent any main() functions in user headers from hijacking the test cases
	target_compile_definitions(${AHP_NAME}_tests PUBLIC main=disabled_main)

	# add Google tests
	add_executable_gtests(${AHP_NAME}_tests TRUE TRUE)

	# also build runtime test code
	if(NOT "${AHP_RUNTIME_TEST_SOURCE}" STREQUAL "")
		add_executable(${AHP_NAME}_runtime_tests ${AHP_RUNTIME_TEST_SOURCE})
		target_link_libraries(${AHP_NAME}_runtime_tests gtest gtest_main testing_utils)
		target_include_directories(${AHP_NAME}_runtime_tests PUBLIC ${HW_DIR})
		target_compile_definitions(${AHP_NAME}_runtime_tests PUBLIC main=disabled_main)

		add_executable_gtests(${AHP_NAME}_runtime_tests FALSE TRUE)
	endif()

	# --------------------------------
	# append 'make grade' commands

	# build tests
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${AHP_NAME} tests, output saved to ${COMPILE_LOG_DIR}/${AHP_NAME}.complog" CACHE "" INTERNAL FORCE)
	set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${AHP_NAME}_tests 1>${COMPILE_LOG_DIR}/${AHP_NAME}.complog 2>&1 || true CACHE "" INTERNAL FORCE)

	if(NOT "${AHP_RUNTIME_TEST_SOURCE}" STREQUAL "")
		# build runtime tests
		set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling ${AHP_NAME} runtime tests" CACHE "" INTERNAL FORCE)
		set(MAKE_GRADE_COMMAND_BODY ${MAKE_GRADE_COMMAND_BODY} COMMAND make ${AHP_NAME}_runtime_tests || true CACHE "" INTERNAL FORCE)
	endif()

endfunction(add_header_problem)



# Function to create a 'make grade' target using the information gathered
# from calling the add_*_problem() functions.

function(gen_grade_target)

	add_custom_target(grade

		# Setup commands
		COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
		COMMAND make clean
		COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
		COMMAND make testing_utils
		
		# include commands built by the other functions
		${MAKE_GRADE_COMMAND_BODY}

		# Grade report generation commands
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
		COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
		COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
		COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

endfunction(gen_grade_target)