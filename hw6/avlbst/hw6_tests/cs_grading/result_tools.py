import cs_grading.executable_tools as exe
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log

####################################################################################################
# Purpose: Defining several strings that can be used for shorthand in many of the methods below.
####################################################################################################
ERESULT_NORUN = '[NORUN]'
ERESULT_TIMEOUT = '[TIMEOUT]'
ERESULT_CRASH = '[CRASH]'
ERESULT_FAIL = '[FAIL]'
ERESULT_PASS = '[PASS]'
ERESULT_OUTPUT = {
    ERESULT_NORUN:   'did not run',
    ERESULT_TIMEOUT: 'timed out',
    ERESULT_CRASH:   'crashed',
    ERESULT_FAIL:    'failed',
    ERESULT_PASS:    'passed',
}

CWARNING_BRNORET = 'control reaches end of non-void function'
CWARNING_RTOP = 'right operand of comma operator has no effect'
CWARNING_ASSIGN = 'assignment used as truth value'
CWARNING_UNINIT = 'uninitialized'
CWARNING_COMPS = 'comparison between signed and unsigned'
CWARNING_UNUSED = 'unused variable'
CWARNING_OUTPUT = {
    CWARNING_BRNORET: CWARNING_BRNORET,
    CWARNING_RTOP:    CWARNING_RTOP,
    CWARNING_ASSIGN:  CWARNING_ASSIGN,
    CWARNING_UNINIT:  CWARNING_UNINIT + ' variable',
    CWARNING_COMPS:   CWARNING_COMPS + ' values',
    CWARNING_UNUSED:  CWARNING_UNUSED,
}

VALGRIND_ERROR_ZERO = 'ERROR SUMMARY: 0 errors from 0 contexts'
VRESULT_IGNORE = '[VIGNORE]'
VRESULT_FAIL = '[VFAIL]'
VRESULT_PASS = '[VPASS]'
VRESULT_OUTPUT = {
    VRESULT_IGNORE,
    VRESULT_FAIL,
    VRESULT_PASS,
}

####################################################################################################
# Purpose: Write a single result line to file.
# Arguments:
#     formatted_file:   Where test results are written.
#     result:           Result code of test.
#     test_name:        Name of test case.
####################################################################################################
def write_result_line(result_file, test_name, result):
    sysio.write_message(
        result_file,
        'Test {} {}\n'.format(test_name, ERESULT_OUTPUT.get(result, '')))

####################################################################################################
# Purpose: Write test results to file.
# Arguments:
#     result_file:      Where test results are written.
#     test_names:       List of test files to be run in order.
#     norun:            set of all tests that did not run
#     timeout:          set of all tests that timed out
#     crashed:          set of all tests that crashed
#     failed:           dictionary of all failed tests with runtime
#     passed:           dictionary of all passed tests with runtime
#     final_log:        If true, print only the final results with failed tests, if any.
#                       If false, print all tests with their result.
####################################################################################################
def write_test_result(result_file,
                      test_names,
                      norun,
                      timeout,
                      crashed,
                      failed,
                      passed,
                      final_log=False,
                      logging_level=log.LOGLEVEL_ERROR
                     ):
    all_failed = list()
    for test_name in test_names:
        if test_name in passed:
            if not final_log:
                write_result_line(result_file, test_name, ERESULT_PASS)
        else:
            all_failed.append(test_name)
            if not (test_name in norun
                    or test_name in timeout
                    or test_name in crashed
                    or test_name in failed):
                log.log_error(
                    '{} not in any execution result set'.format(test_name),
                    logging_level)
            elif not final_log:
                if test_name in norun:
                    write_result_line(result_file, test_name, ERESULT_NORUN)
                elif test_name in timeout:
                    write_result_line(result_file, test_name, ERESULT_TIMEOUT)
                elif test_name in crashed:
                    write_result_line(result_file, test_name, ERESULT_CRASH)
                elif test_name in failed:
                    write_result_line(result_file, test_name, ERESULT_FAIL)

    sysio.write_message(result_file, '\n')
    if not all_failed:
        sysio.write_message(result_file, 'All Test Cases Passed')
    else:
        sysio.write_message(result_file, 'Failed ' + str(len(all_failed)) + ' tests:\n')
        for ftest in all_failed:
            sysio.write_message(result_file, '\tTest ' + ftest + '\n')

####################################################################################################
# Purpose: Write a single formatted line to file.
# Arguments:
#     formatted_file:   Where test results are written.
#     result:           Result code of test.
#     test_name:        Name of test case.
#     runtime:          Runtime of the test, if available.
####################################################################################################
def write_formatted_line(formatted_file, test_name, result, vresult, runtime=None):
    if runtime is not None:
        formatted_line = '{} {} {} ({:.3f})\n'.format(result, vresult, test_name, runtime)
    else:
        formatted_line = '{} {} {}\n'.format(result, vresult, test_name)

    sysio.write_message(formatted_file, formatted_line)

####################################################################################################
# Purpose: Write formatted test results to file.
# Arguments:
#     formatted_file:   Where test results are written.
#     test_names:       List of test files to be run in order.
#     norun:            Set of all tests that did not run
#     timeout:          Set of all tests that timed out
#     crashed:          Set of all tests that crashed
#     failed:           Dictionary of all failed tests with runtime
#     passed:           Dictionary of all passed tests with runtime
####################################################################################################
def write_formatted_result(formatted_file,
                           test_names,
                           valgrind,
                           norun,
                           timeout,
                           crashed,
                           failed,
                           passed,
                           logging_level=log.LOGLEVEL_ERROR
                          ):
    for idx, test_name in enumerate(test_names):
        result = None
        vcode = valgrind[idx] if idx < len(valgrind) else exe.EXE_ERROR
        runtime = None
        if test_name in passed:
            result = ERESULT_PASS
            runtime = passed[test_name]
        elif test_name in norun:
            result = ERESULT_NORUN
        elif test_name in timeout:
            result = ERESULT_TIMEOUT
        elif test_name in crashed:
            result = ERESULT_CRASH
        elif test_name in failed:
            result = ERESULT_FAIL
            runtime = failed[test_name]
        else:
            log.log_error('{} not in any execution result set'.format(test_name), logging_level)

        if vcode == exe.EXE_ERROR:
            vresult = VRESULT_IGNORE
        elif vcode == exe.VALGRIND_SUCCESS:
            vresult = VRESULT_PASS
        elif vcode == exe.VALGRIND_ERROR or vcode == exe.VALGRIND_SIGSEGV:
            vresult = VRESULT_FAIL
        else:
            log.log_warning('Unknown return code ' + str(vcode), logging_level)
            vresult = VRESULT_IGNORE

        write_formatted_line(formatted_file, test_name, result, vresult, runtime)

####################################################################################################
# Purpose: Write a single formatted line to file.
# Arguments:
#     formatted_line:   The string that contains formatted result line.
# Return Values:
#     result:           Result code of test case.
#     test_name:        Name of test.
#     runtime:          Runtime of test, if available.
####################################################################################################
def read_formatted_line(formatted_line, logging_level=log.LOGLEVEL_ERROR):
    result = None
    vresult = None
    test_name = ''
    runtime = None

    stripped_line = formatted_line.strip()
    for result_code in ERESULT_OUTPUT:
        if stripped_line.find(result_code) != -1:
            if result is not None:
                log.log_error(
                    'Multiple test result code in line ' + formatted_line,
                    logging_level)
            else:
                result = result_code

    for result_code in VRESULT_OUTPUT:
        if stripped_line.find(result_code) != -1:
            if vresult is not None:
                log.log_error(
                    'Multiple valgrind result code in line ' + formatted_line,
                    logging_level)
            else:
                vresult = result_code

    if result is None:
        log.log_error(
            'Failed to identify test result in line ' + formatted_line,
            logging_level)
    if vresult is None:
        log.log_error(
            'Failed to identify valgrind result in line ' + formatted_line,
            logging_level)
    if result is not None and vresult is not None:
        stripped_line = stripped_line.replace(result, '').strip()
        stripped_line = stripped_line.replace(vresult, '').strip()
        runtime_start = stripped_line.find('(')
        if runtime_start == -1:
            test_name = stripped_line
        else:
            test_name = stripped_line[:runtime_start].strip()
            runtime_end = stripped_line.find(')')
            runtime = float(stripped_line[runtime_start + 1:runtime_end])
    return test_name, result, vresult, runtime

####################################################################################################
# Purpose: Write formatted result file.
# Arguments:
#     formatted_file:   The formatted result file.
# Return Values:
#     test_names:       List of tuples of test result and test name.
####################################################################################################
def read_formatted_result(formatted_file,
                          logging_level=log.LOGLEVEL_ERROR
                         ):
    test_names = list()
    if not sysio.exist_file(formatted_file):
        log.log_error('Cannot find formatted result ' + formatted_file, logging_level)
    else:
        form = open(formatted_file, mode='r', errors='ignore')
        lines = form.readlines()
        form.close()
        for formatted_line in lines:
            test_name, result, vresult, _ = read_formatted_line(
                formatted_line,
                logging_level=logging_level)
            test_names.append((test_name, result, vresult))
    return test_names

####################################################################################################
# Purpose: Finf warnings in compile result.
# Arguments:
#      compile_result:        The valgrind result file
#      logging_level:    Logging level.
# Return Value:
#      Returns the set of warnings codes.
####################################################################################################
def read_compile_result(compile_result, logging_level=log.LOGLEVEL_ERROR):
    warnings = set()
    if not sysio.exist_file(compile_result):
        log.log_error('Cannot find compile ' + compile_result, logging_level)
    else:
        comp = open(compile_result, mode='r', errors='ignore')
        lines = comp.readlines()
        comp.close()
        for output in lines:
            for warning in CWARNING_OUTPUT:
                if output.find(warning) != -1:
                    warnings.add(warning)
    return warnings

####################################################################################################
# Purpose: Count the number of valgrind reports with zero error
# Arguments:
#      valgrind_result:  The valgrind result file
#      logging_level:    Logging level.
# Return Value:
#      Returns the number of runs with zero valgrind errors.
####################################################################################################
def read_valgrind_result(valgrind_result, logging_level=log.LOGLEVEL_ERROR):
    zero_error_count = 0
    if not sysio.exist_file(valgrind_result):
        log.log_error('Cannot find valgrind result ' + valgrind_result, logging_level)
    else:
        comp = open(valgrind_result, mode='r', errors='ignore')
        lines = comp.readlines()
        comp.close()
        for output in lines:
            if output.find(VALGRIND_ERROR_ZERO) != -1:
                zero_error_count += 1
    return zero_error_count
