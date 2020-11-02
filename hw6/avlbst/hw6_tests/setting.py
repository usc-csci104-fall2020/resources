import sys
sys.path.insert(0, 'tests')
import cs_grading.logging_tools as log

# Global test settings

# whether test output is removed
REMOVE_OUTPUT = 0

# whether to open result file and valgrind file
OPEN_RESULT = 0

# use detailed results in file comparison
DETAILED_RESULT = 1

# DO NOT MODIFY AFTER THIS
TEXT_EDITOR = 'subl'
COMPILE_FLAGS = []
LOGGING_LEVEL = log.LOGLEVEL_INFO # none, error, warning, or all
GENERATE_GRADE_REPORT = True # Do now turn on when student runs test
OVERWRITE_REPORT = True # Should existing report be overwritten
