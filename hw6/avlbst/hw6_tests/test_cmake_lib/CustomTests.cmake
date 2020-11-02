# File for our custom test creation macros


# modified version of gtest_add_test that has an option to run the tests in Valgrind,
# and to start the debugger on them
# Scans the given executable's sources for GTest tests, then adds them as CTest tests
function(add_executable_gtests executable USE_VALGRIND MAKE_DEBUG_TARGETS)

    # obtain sources used for building the executable
    get_property(SOURCES_TO_CHECK TARGET ${executable} PROPERTY SOURCES)

    list(REMOVE_DUPLICATES SOURCES_TO_CHECK)

    set(gtest_case_name_regex ".*\\( *([A-Za-z_0-9]+) *, *([A-Za-z_0-9]+) *\\).*")
    set(gtest_test_type_regex "(TYPED_TEST|TEST_?[FP]?)")

    set(NUM_TESTS_FOUND 0)

    foreach(source ${SOURCES_TO_CHECK})

        file(READ "${source}" contents)

        string(REGEX MATCHALL "${gtest_test_type_regex} *\\(([A-Za-z_0-9 ,]+)\\)" found_tests "${contents}")

        foreach(hit ${found_tests})
          string(REGEX MATCH "${gtest_test_type_regex}" test_type ${hit})

          # Parameterized tests have a different signature for the filter
          if("x${test_type}" STREQUAL "xTEST_P")
            string(REGEX REPLACE ${gtest_case_name_regex}  "*/\\1.\\2/*" test_name ${hit})
          elseif("x${test_type}" STREQUAL "xTEST_F" OR "x${test_type}" STREQUAL "xTEST")
            string(REGEX REPLACE ${gtest_case_name_regex} "\\1.\\2" test_name ${hit})
          elseif("x${test_type}" STREQUAL "xTYPED_TEST")
            string(REGEX REPLACE ${gtest_case_name_regex} "\\1/*.\\2" test_name ${hit})
          else()
            message(WARNING "Could not parse GTest ${hit} for adding to CTest.")
            continue()
          endif()

          if(NOT TEST ${test_name})

            if(USE_VALGRIND)
              add_test(NAME ${test_name} COMMAND valgrind ${VALGRIND_ARGS} $<TARGET_FILE:${executable}> --gtest_filter=${test_name})
            else()
              add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${executable}> --gtest_filter=${test_name})
            endif()

            if(MAKE_DEBUG_TARGETS)
              # add debugging target
              # message("Adding custom target \"debug-${test_name}\" with command \"gnome-terminal -e \"gdb --args $<TARGET_FILE:${executable}> --gtest_filter=${test_name}\" &\"")

              add_custom_target(debug-${test_name}
                COMMAND gdb --args $<TARGET_FILE:${executable}> --gtest_filter=${test_name}
                WORKING_DIRECTORY ${HW_DIR}
                VERBATIM
                COMMENT "Debugging ${test_name} with GDB...")
            endif()

          endif()

          math(EXPR NUM_TESTS_FOUND "${NUM_TESTS_FOUND} + 1")
        endforeach()

    endforeach()

    message(STATUS "Found ${NUM_TESTS_FOUND} GTests from ${executable}")
endfunction()

# custom test target that prints error messages on failure (for some reason it doesn't do this by default???)
# from https://stackoverflow.com/questions/5709914/using-cmake-how-do-i-get-verbose-output-from-ctest
add_custom_target(check 
    COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}          # sean for new source files and tests 
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}  # force rebuild of changed source files
    COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -j 2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# write CTest config file to  increase length of saved output for passed tests
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/CTestCustom.cmake CONTENT "
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 307200)
")

