
# build kwsys dependency library
add_definitions(-D_DEFAULT_SOURCE)
set(KWSYS_NAMESPACE kwsys)
set(KWSYS_USE_SystemTools TRUE)
set(KWSYS_USE_RegularExpression TRUE)
set(KWSYS_USE_Process TRUE)
set(KWSYS_HEADER_ROOT ${CMAKE_CURRENT_BINARY_DIR}/generated_headers)
add_subdirectory(kwsys)

# build libperf performance measurement library
add_subdirectory(libperf)


set(TESTING_UTILS_SOURCES
	runtime_evaluator.cpp
	random_generator.cpp
	misc_utils.cpp
	user_code_runner.cpp
	rang.h)

add_library(testing_utils STATIC ${TESTING_UTILS_SOURCES})
target_include_directories(testing_utils PUBLIC . ${CMAKE_CURRENT_BINARY_DIR}/generated_headers)
target_link_libraries(testing_utils gtest kwsys perf)

# tell utils library about the directory structure
target_compile_definitions(testing_utils PUBLIC TEST_BINARY_DIR=\"${CMAKE_BINARY_DIR}\" USER_CODE_DIR=\"${HW_DIR}\")
