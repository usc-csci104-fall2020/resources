# Sets up compilation flags for all CS104 tests


# force build type to always be debug (for better Valgrind and GDB output)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

# debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# use C99 and C++11, with no extensions
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS FALSE)

