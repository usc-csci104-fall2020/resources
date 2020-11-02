import cs_grading.executable_tools as exe
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log

####################################################################################################
# Purpose: Defining several strings that can be used for shorthand in many of the methods below.
# Definitions:
#      GRESULT_RUN:    The output prefix when a gtest is ran..
#      GRESULT_FAILED: The output prefix when a gtest failde.
#      GRESULT_PASSED: The output prefix when a gtest passed.
####################################################################################################
GRESULT_RUN = '[ RUN      ] '
GRESULT_FAILED = '[  FAILED  ] '
GRESULT_PASSED = '[       OK ] '
GTEST_MACRO = 'TEST_F'

####################################################################################################
# Purpose: Runs a single gtest.
# Arguments:
#     executable_path:  The path to the executable. For example, './'.
#     kwargs:           See executable_tools.run_executable for more options.
# Return Values:
#     Returns execution result and return code of execution.
#     Execution result:
#         EXE_ERROR if there's an error and the executable did not run.
#         EXE_SUCCESS if there's no timeout.
#         EXE_TIMEOUT if there's timeout.
####################################################################################################
def run_gtest(executable_path, **kwargs):
    if kwargs is None:
        kwargs = dict()
    output_result = kwargs.get('output_result', None)

    extra_arguments = []
    if output_result is not None:
        extra_arguments = ['>', output_result]

    kwargs['extra_arguments'] = extra_arguments
    killed, _, retcode = exe.run_executable(executable_path, **kwargs)
    return killed, retcode

####################################################################################################
# Purpose: Create a list of gtest filters.
# Arguments:
#     filter_string:    The filter string before substitution.
#     iterable:         An iterable object containing the values to substitute into filter_string.
#     subkey:           Key in filter_string if it's key based, None if it's position.
# Return Values:
#     Returns a list of gtest filter strings.
####################################################################################################
def create_gtest_filter_range(filter_string, iterable, subkey=None):
    gtest_filter = list()
    for curr in iterable:
        args = ()
        kwargs = dict()
        if subkey is None:
            args = (curr,)
        else:
            kwargs = {subkey: curr}
        gtest_filter.append(filter_string.format(*args, **kwargs))
    return gtest_filter

####################################################################################################
# Purpose: Runs a gtest with filter and additional options.
# Arguments:
#     executable_path:  The path to the executable. For example, './'.
#     gtest_filters:    A list of filter text to be used.
#     output_result:    Output result file if redirection is desired.
#     separate_result:  Should a separate result file be created for each filtered run.
#     logging_level:    Logging level.
#     kwargs:           See executable_tools.run_executable for more options.
# Return Values:
#     Returns a list of execution result and return codes.
#     Execution result:
#         EXE_ERROR if there's an error and the executable did not run.
#         EXE_SUCCESS if there's no timeout.
#         EXE_TIMEOUT if there's timeout.
####################################################################################################
def run_gtest_with_filter(executable_path, gtest_filters, **kwargs):
    if kwargs is None:
        kwargs = dict()
    output_result = kwargs.get('output_result', None)
    separate_result = kwargs.get('separate_result', True)

    filter_arg = '--gtest_filter='
    temp_log_file = 'temp_gtest_log.txt'
    result = list()
    retcodes = list()
    for filtered_test in gtest_filters:
        full_filter = [filter_arg + filtered_test]
        extra_arguments = []
        if output_result is not None:
            if separate_result:
                separate_result = output_result + filtered_test + '.txt'
                extra_arguments = ['>', separate_result]
            else:
                extra_arguments = ['>', temp_log_file]

        extra_arguments_filtered = full_filter + extra_arguments
        kwargs['extra_arguments'] = extra_arguments_filtered
        killed, _, retcode = exe.run_executable(exe.fix_executable_path(executable_path), **kwargs)
        result.append(killed)
        retcodes.append(retcode)
        if output_result is not None and not separate_result:
            sysio.write_file_contents(output_result, temp_log_file)
            sysio.write_message(output_result, '\n\n')
            sysio.clean_file(temp_log_file)
    return result, retcodes

####################################################################################################
# Purpose: Load all gtest test names in a gtest file.
# Arguments:
#     gtest_file:       The file where test cases are found.
# Return Values:
#     Returns a list of gtest test names.
####################################################################################################
def load_gtest_names(gtest_file, logging_level=log.LOGLEVEL_ERROR):
    def parse_test_name(line, logging_level=log.LOGLEVEL_ERROR):
        suite_name = ''
        test_name = ''
        if (line.find('(') == -1
                or line.find(')') == -1
                or line.find(',') == -1):
            log.log_error('Malformed gtest macro ' + line, logging_level)
        else:
            line = line.replace(GTEST_MACRO, '')
            start = line.find('(')
            end = line.find(')')
            separator = line.find(',')
            suite_name = line[start + 1:separator].strip()
            test_name = line[separator + 1:end].strip()
        return suite_name + '.' + test_name

    ### load_test_case body ###
    test_names = list()
    if not sysio.exist_file(gtest_file):
        log.log_error('Cannot find ' + gtest_file, logging_level)
        return test_names

    test_file = open(gtest_file, 'r')
    for line in test_file.readlines():
        if line.find(GTEST_MACRO) != -1:
            test_names.append(parse_test_name(line))
    test_file.close()
    return test_names

####################################################################################################
# Purpose: Run all gtest test cases in file separately.
# Arguments:
#     source_file:      Source file of gtest.
#     target_file:      Executable target name.
#     output_result:    Where gtest results are stored.
#     See executable_tools.compile_code for all compile options.
#     See executable_tools.run_executable for all execution options.
# Return Values:
#     Two list, three sets and two dictionaries.
#     1. list of gtest test names.
#     2. list of return codes.
#     2. set of tests that are not ran.
#     3. set of tests that timed out.
#     4. set of tests that crashed.
#     5. dictionary of tests that failed with their runtime.
#     6. dictionary of tests that succeeded with their runtime.
####################################################################################################
def run_gtest_in_file(source_file, target_file, output_result, **kwargs):
    if kwargs is None:
        kwargs = dict()
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    test_sorted = load_gtest_names(source_file)
    retcodes = list()
    norun = set()
    timeout = set()
    crashed = set()
    failed = dict()
    passed = dict()

    kwargs['use_gtest'] = True
    kwargs['compile_file_append'] = True
    compile_result = exe.compile_code(
        [source_file],
        target_file,
        **kwargs,
    )

    kwargs['output_result'] = output_result
    kwargs['separate_result'] = False
    run_result, retcodes = run_gtest_with_filter(
        target_file,
        test_sorted,
        **kwargs,
    )

    crashed, failed, passed = read_gtest_result(
        output_result,
        logging_level=logging_level)

    for test_num, test_name in enumerate(test_sorted):
        if compile_result != exe.EXE_SUCCESS or run_result[test_num] == exe.EXE_ERROR:
            norun.add(test_name)
        elif run_result[test_num] == exe.EXE_TIMEOUT:
            timeout.add(test_name)

    return test_sorted, retcodes, norun, timeout, crashed, failed, passed

####################################################################################################
# Purpose: Runs a all gtest cpp files in a directory.
# Arguments:
#     test_sorted:      List of test files to be run in order.
#     source_dir:       Directory that contains all gtest source files.
#     output_dir:       Where individual gtest results are stored.
#     target_dir:       Where compiled gtest executables are stored.
#     logging_level:    Logging level.
#     See executable_tools.compile_code for all compile options.
#     See executable_tools.run_executable for all execution options.
# Return Values:
#     One list, three sets and two dictionaries.
#     1. list of return codes.
#     2. set of tests that are not ran.
#     3. set of tests that timed out.
#     4. set of tests that crashed.
#     5. dictionary of tests that failed with their runtime.
#     6. dictionary of tests that succeeded with their runtime.
####################################################################################################
def run_gtest_in_dir(test_sorted,
                     source_dir,
                     output_dir,
                     target_dir,
                     **kwargs
                    ):
    if kwargs is None:
        kwargs = dict()
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    retcodes = list()
    norun = set()
    timeout = set()
    crashed = set()
    failed = dict()
    passed = dict()

    for test_name in test_sorted:
        t_source = source_dir + '/' + test_name + '.cpp'
        t_output = output_dir + '/' + test_name + '.txt'
        t_target = target_dir + '/' + test_name

        sysio.clean_file(t_target)
        sysio.clean_file(t_output)
        kwargs['use_gtest'] = True
        kwargs['compile_file_append'] = True
        compile_result = exe.compile_code([t_source], t_target, **kwargs)

        if compile_result != exe.EXE_SUCCESS:
            norun.add(test_name)
            retcodes.append(exe.EXE_ERROR)
        else:
            kwargs['extra_arguments'] = ['>', t_output]
            killed, _, retcode = exe.run_executable(
                exe.fix_executable_path(t_target),
                **kwargs)
            retcodes.append(retcode)
            if killed == exe.EXE_ERROR:
                norun.add(test_name)
            elif killed == exe.EXE_TIMEOUT:
                timeout.add(test_name)
            else:
                t_crahed, t_failed, t_passed = read_gtest_result(
                    t_output,
                    logging_level=logging_level)
                for _, value in t_passed.items():
                    passed[test_name] = value
                for _, value in t_failed.items():
                    failed[test_name] = value
                for _ in t_crahed:
                    crashed.add(test_name)
                if not t_crahed and not t_failed and not t_passed:
                    norun.add(test_name)

    return retcodes, norun, timeout, crashed, failed, passed

####################################################################################################
# Purpose: Check gtest execution result
# Arguments:
#      comp_file:        The gtest result file
#      logging_level:    Logging level.
# Return Value:
#      1. The set of tests that did not terminate (neither passed nor failed is printed)
#      2. The dictionary of all failed tests and their runtime in seconds.
#      3. The dictionary of all passed tests and their runtime in seconds.
####################################################################################################
def read_gtest_result(comp_file, logging_level=log.LOGLEVEL_ERROR):
    def parse_test_name(test_output, result):
        space = test_output.find(result)
        test_output = test_output[space + len(result):].strip()
        test_name = None
        runtime = None
        space = test_output.find(' (')
        if space != -1:
            test_name = test_output[:space]
            test_output = test_output[space + 2:]
            space = test_output.find(' ms)')
            if space != -1:
                runtime = int(test_output[:space]) / 1000.0
        else:
            test_name = test_output
        return test_name, runtime

    ### read_gtest_result body ###
    run = set()
    no_terminate = set()
    failed = set()
    passed = set()
    failed_runtime = dict()
    passed_runtime = dict()
    if not sysio.exist_file(comp_file):
        log.log_error('Cannot find ' + comp_file, logging_level)
    else:
        with open(comp_file, mode='r', errors='ignore') as comp:
            lines = comp.readlines()
            for output in lines:
                output = output.replace('\n', '')
                if output.find(GRESULT_RUN) != -1:
                    test, _ = parse_test_name(output, GRESULT_RUN)
                    run.add(test)
                elif output.find(GRESULT_FAILED) != -1:
                    test, runtime = parse_test_name(output, GRESULT_FAILED)
                    if test != '' and runtime is not None:
                        failed.add(test)
                        failed_runtime[test] = runtime
                elif output.find(GRESULT_PASSED) != -1:
                    test, runtime = parse_test_name(output, GRESULT_PASSED)
                    if test != '' and runtime is not None:
                        passed.add(test)
                        passed_runtime[test] = runtime
        no_terminate = run - failed - passed
    return no_terminate, failed_runtime, passed_runtime
