include_directories(.)

add_header_problem(
	NAME bst 
	TEST_SOURCE 
		test_insert.cpp
	    test_remove.cpp
	    test_balance.cpp
 	RUNTIME_TEST_SOURCE
 		bst_runtime_tests.cpp)
	  
