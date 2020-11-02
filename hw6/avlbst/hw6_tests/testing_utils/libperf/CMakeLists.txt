## CS104 CMake buildfile for the libperf performance counter.

# Yes, this program is GPL licensed, but I figure that this counts as educational fair use, so it should be OK

add_library(perf STATIC libperf.c)
target_include_directories(perf PUBLIC .)