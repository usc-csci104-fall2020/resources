import cs_grading.comparison_tools as comp
import cs_grading.executable_tools as exe
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log
import cs_grading.result_tools as res

####################################################################################################
# Purpose: Runs executable N times, each time passing in an argument in the argument list.
# Arguments:
#     executable_path:  The path to the executable. For example, './'.
#     test_names:       List of unique identifier of each test.
#     test_args:        List of list, where each sub-list is the list of arguments passed
#                       as command line argument to the executable.
#     logging_level:    Logging level.
#     kwargs:           See executable_tools.run_executable for more options.
# Return Values:
#     One list and three sets.
#     1. set of tests that are not ran.
#     2. set of tests that timed out.
#     3. dictionary of tests that finished running with their runtime.
####################################################################################################
def run_tests_in_list(executable_path, test_names, test_args, **kwargs):
    if kwargs is None:
        kwargs = dict()
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    retcodes = list()
    all_norun = set()
    all_timeout = set()
    all_finished = dict()

    if len(test_names) != len(test_args):
        log.log_error('Found {} tests but {} test arguments'.format(
            str(len(test_names)), str(len(test_args))), logging_level)
        return set(x for x in test_names), all_timeout, all_finished

    for i, test_name in enumerate(test_names):
        if not sysio.exist_file(executable_path):
            log.log_warning('Executable {} not found'.format(executable_path), logging_level)
            all_norun.add(test_name)
        else:
            kwargs['extra_arguments'] = test_args[i]
            killed, runtime, retcode = exe.run_executable(executable_path, **kwargs)
            retcodes.append(retcode)
            if killed == exe.EXE_ERROR:
                all_norun.add(test_name)
            elif killed == exe.EXE_TIMEOUT:
                all_timeout.add(test_name)
            else:
                all_finished[test_name] = runtime
    return retcodes, all_norun, all_timeout, all_finished

####################################################################################################
# Purpose: Check test output for a list of tests.
# Arguments:
#     test_names:       List of unique identifier of each test.
#     solution_list:    List of solution files (expected output).
#     output_list:      List of output files to compare to solution file.
#     result_file:      Where test results are written.
#     ordered_compare:  Does order matter during comparison.
#     logging_level:    Logging level.
#     See comparison_tools.compare_files for all options.
# Return Values:
#     Two sets.
#     1. set of tests that failed.
#     2. set of tests that passed.
####################################################################################################
def check_test_output(test_names,
                      solution_list,
                      output_list,
                      result_file,
                      ordered_compare,
                      **kwargs
                     ):
    if kwargs is None:
        kwargs = dict()
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    all_failed = set()
    all_passed = set()

    if len(test_names) != len(output_list):
        log.log_error('Found {} test names but {} test output'.format(
            str(len(test_names)), str(len(output_list))), logging_level)
        return set(x for x in test_names), all_passed

    if len(solution_list) != len(output_list):
        log.log_error('Found {} test solution but {} test output'.format(
            str(len(solution_list)), str(len(output_list))), logging_level)
        return set(x for x in test_names), all_passed

    for i, test_name in enumerate(test_names):
        t_solution = solution_list[i]
        t_output = output_list[i]
        if not sysio.exist_file(t_solution):
            log.log_error('Cannot find solution file ' + t_solution, logging_level)
            all_failed.add(test_name)
        else:
            _, missing, extra = comp.compare_files(
                t_solution,
                t_output,
                result_file,
                ordered_compare=ordered_compare,
                **kwargs
                )

            sysio.write_message(result_file, '\n\n')
            if missing == 0 and extra == 0:
                all_passed.add(test_name)
                res.write_result_line(result_file, test_name, res.ERESULT_PASS)
            else:
                all_failed.add(test_name)
                res.write_result_line(result_file, test_name, res.ERESULT_FAIL)
    return all_failed, all_passed

####################################################################################################
# Purpose: Get runtime of failed and passed tests.
# Arguments:
#     test_names:       Dictionary of all test names with runtime.
#     failed:           Set of failed test names.
#     passed:           Set of passed test names.
# Return Values:
#     Two dictionaries.
#     1. dictionary of failed tests with runtime.
#     2. dictionary of passed tests with runtime.
####################################################################################################
def get_test_runtime(test_names, failed, passed, logging_level=log.LOGLEVEL_ERROR):
    failed_runtime = dict()
    passed_runtime = dict()

    for test_name, runtime in test_names.items():
        if test_name in failed:
            failed_runtime[test_name] = runtime
        elif test_name in passed:
            passed_runtime[test_name] = runtime
        else:
            log.log_error('{} not in any execution result set'.format(test_name), logging_level)

    return failed_runtime, passed_runtime
