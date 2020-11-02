include_directories(. ../bst_tests)

add_header_problem(
	NAME avl 
	TEST_SOURCE 
		test_insert.cpp
   	 	test_remove.cpp
	RUNTIME_TEST_SOURCE
 		avl_runtime_tests.cpp)
