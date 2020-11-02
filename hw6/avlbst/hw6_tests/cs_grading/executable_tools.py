import os
import resource
import subprocess
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log

####################################################################################################
# Purpose: Defining several constants that can be used for shorthand in many of the methods below.
# Definitions:
#      CPPFLAGS:    Default cpp compiler flags.
#      VALGRIND:    Contains the command needed for running an executable with valgrind.
#      GTEST:       Contains the compilation instruction needed for compiling GTest executable
####################################################################################################
CPPFLAGS = ['-g', '-Wall', '-std=c++11']
GTEST = ['-I', '/usr/include/gtest/', '-l', 'gtest', '-l', 'gtest_main', '-pthread']
VALGRIND = ['valgrind', '--tool=memcheck', '--leak-check=yes', '--error-exitcode=42']

EXE_ERROR = -1
EXE_SUCCESS = 0
EXE_TIMEOUT = 1

VALGRIND_SUCCESS = 0
VALGRIND_ERROR = 42
VALGRIND_SIGSEGV = -11
VALGRIND_SIGABRT = -6
VALGRIND_SIGFPE = -8

def get_redirection_argument(compile_file=None, compile_file_append=True):
    redirection_args = []
    if compile_file is not None:
        compile_file = os.path.abspath(compile_file)
        if compile_file_append:
            compile_file_append = '>>'
        else:
            compile_file_append = '>'
        redirection_args = [
            compile_file_append,
            compile_file,
            '2' + compile_file_append,
            compile_file
        ]
    return redirection_args

####################################################################################################
# Purpose: Compile students code using make file.
# Arguments:
#     make_command:        The make file rule target.
#     makefile_dir:        Director of make file.
#     compile_file:        File name where compile result is redirected. Default is None.
#     compile_file_append: Should compile result be appended. Default to True.
#     logging_level:       Logging level.
# Return Values:
#     Returns whether compilation was successful.
#     EXE_ERROR if there's an error and the executable did not run.
#     EXE_SUCCESS if there's no timeout.
####################################################################################################
def make_code(make_command, makefile_dir, **kwargs):
    if kwargs is None:
        kwargs = dict()
    compile_file = kwargs.get('compile_file', None)
    compile_file_append = kwargs.get('compile_file_append', True)
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    redirection_args = get_redirection_argument(compile_file, compile_file_append)
    cwd = os.getcwd()
    os.chdir(makefile_dir)
    executable_path = 'make'
    extra_arguments = [make_command] + redirection_args

    _, _, retcode = run_executable(executable_path,
                                   extra_arguments=extra_arguments,
                                   use_valgrind=False,
                                   timeout=None,
                                   logging_level=logging_level,
                                   logging_force_suppressed=True)
    os.chdir(cwd)
    return retcode

####################################################################################################
# Purpose: Compile students code into an executable.
# Arguments:
#     source_files:        The list of source files needed to compile an executable.
#     compiler:            The compiler that will be used in case a makefile is not provided.
#                          Default is 'g++'
#     compile_flags:       Any flags you wish to use when compiling. Default is CPPFLAGS.
#     target:              Name of the executable that is created.
#     use_gtest:           Pass 1 if no makefile is provided and compilation requires Google Tests.
#     compile_file_append: File name where compile result is redirected. Default is None.
#     compile_file:  Should compile result be appended. Default to True.
#     logging_level:       Logging level.
# Return Values:
#     Returns whether compilation was successful.
#     EXE_ERROR if there's an error and the executable did not run.
#     EXE_SUCCESS if there's no timeout.
####################################################################################################
def compile_code(source_files, target, **kwargs):
    if kwargs is None:
        kwargs = dict()
    compiler = kwargs.get('compiler', 'g++')
    compile_flags = kwargs.get('compile_flags', CPPFLAGS)
    use_gtest = kwargs.get('use_gtest', False)
    compile_file = kwargs.get('compile_file', None)
    compile_file_append = kwargs.get('compile_file_append', True)
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    redirection_args = get_redirection_argument(compile_file, compile_file_append)

    executable_path = compiler
    extra_arguments = compile_flags + source_files
    if use_gtest:
        extra_arguments += GTEST
    extra_arguments += ['-o', target] + redirection_args

    _, _, retcode = run_executable(executable_path,
                                   extra_arguments=extra_arguments,
                                   use_valgrind=False,
                                   timeout=None,
                                   logging_level=logging_level,
                                   logging_force_suppressed=True)
    return retcode

####################################################################################################
# Purpose: Fixing executable path by appending './' to front if no path is specified
# Arguments:
#     executable_path: executable path to be fixed
# Return Value:
#     Returns a fixed executable path
####################################################################################################
def fix_executable_path(executable_path):
    for i in executable_path:
        if i == '/':
            return executable_path
    return './' + executable_path

####################################################################################################
# Purpose: Runs an executable with additional options.
# Arguments:
#     executable_path: The fuul path to the executable. For example, './exe'.
#     extra_arguments: Any extra commands that are needed to run the executable. For example,
#                      run_executable('./ex', ['test.in', 'test.out']) runs as follows:
#                      ./ex test.in test.out
#                      This can also be used to redirect input and output. For example,
#                      run_executable('./ex', ['<', 'test.in', '>', 'test.out']) runs as follows:
#                      ./ex < test.in > test.out
#      use_valgrind:   An optional argument to run an executable with valgrind. Not used by default.
#      valgrind_file:  Name of valgrind log file.
#      timeout:        An optional argument to timeout the program. By default, it is not used.
#      logging_level:  Logging level.
#      logging_force_suppressed:  Force suppressing executable running log.
# Return Values:
#      Returns a tuple of three elements.
#      1. Result:  Execution result.
#                  EXE_ERROR if there's an error and the executable did not run.
#                  EXE_SUCCESS if there's no timeout.
#                  EXE_TIMEOUT if there's timeout.
#      2. Child time: Total time spent in user mode for the child process in seconds.
#      2. Return code: Return code from executable. undefined if executable did not run.
####################################################################################################
def run_executable(executable_path, **kwargs):
    if kwargs is None:
        kwargs = dict()
    extra_arguments = kwargs.get('extra_arguments', list())
    use_valgrind = kwargs.get('use_valgrind', False)
    valgrind_file = kwargs.get('valgrind_file', None)
    timeout = kwargs.get('timeout', None)
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)
    logging_force_suppressed = kwargs.get('logging_force_suppressed', False)

    killed = EXE_ERROR
    utime = EXE_ERROR
    retcode = EXE_ERROR
    error = False

    args = []
    if use_valgrind:
        if valgrind_file is None:
            log.log_warning('valgrind turned on but no valgrind log file speficied', logging_level)
        temp_valgrind_log = 'temp_valgrind_log.txt'
        args.extend(VALGRIND)
        args.append('--log-file=' + temp_valgrind_log)

    redirected_stdin_file = None
    redirected_stdout_mode = None
    redirected_stdout_file = None
    redirected_stderr_mode = None
    redirected_stderr_file = None

    i = 0
    while i < len(extra_arguments):
        if extra_arguments[i] == '<':
            # redirect input
            if i + 1 >= len(extra_arguments):
                log.log_error('Found input redirection with no input file', logging_level)
                error = True
                break
            else:
                redirected_stdin_file = extra_arguments[i + 1]
                del extra_arguments[i + 1]
                del extra_arguments[i]
        elif extra_arguments[i] == '>' or extra_arguments[i] == '>>':
            # redirect output
            if extra_arguments[i] == '>':
                redirected_stdout_mode = 'w'
            else:
                redirected_stdout_mode = 'a'
            if i + 1 >= len(extra_arguments):
                log.log_error('Found output redirection with no output file', logging_level)
                error = True
                break
            else:
                redirected_stdout_file = extra_arguments[i + 1]
                del extra_arguments[i + 1]
                del extra_arguments[i]
        elif extra_arguments[i] == '2>' or extra_arguments[i] == '2>>':
            # redirect output
            if extra_arguments[i] == '2>':
                redirected_stderr_mode = 'w'
            else:
                redirected_stderr_mode = 'a'
            if i + 1 >= len(extra_arguments):
                log.log_error('Found error redirection with no output file', logging_level)
                error = True
                break
            else:
                redirected_stderr_file = extra_arguments[i + 1]
                del extra_arguments[i + 1]
                del extra_arguments[i]
        else:
            i += 1

    if not error:
        extra_arguments = [executable_path] + extra_arguments
        if not logging_force_suppressed:
            log.log_info('Running ' + ' '.join(extra_arguments), log.LOGLEVEL_INFO)
        args.extend(extra_arguments)

        if redirected_stdout_file is not None:
            redirected_stdout_file = open(redirected_stdout_file, redirected_stdout_mode)
        if redirected_stderr_file is not None:
            redirected_stderr_file = open(redirected_stderr_file, redirected_stderr_mode)
        if redirected_stdin_file is not None:
            redirected_stdin_file = open(redirected_stdin_file, 'r')

        try:
            start_time = resource.getrusage(resource.RUSAGE_CHILDREN).ru_utime
            proc = subprocess.Popen(args,
                                    stdout=redirected_stdout_file,
                                    stderr=redirected_stderr_file,
                                    stdin=redirected_stdin_file)
            proc.communicate(timeout=timeout)
            killed = EXE_SUCCESS
            retcode = proc.returncode
        except subprocess.TimeoutExpired:
            log.log_warning('Executable {} timed out'.format(executable_path), logging_level)
            killed = EXE_TIMEOUT
            proc.kill()
        except OSError:
            log.log_warning('Executable {} not found'.format(executable_path), logging_level)
            killed = EXE_ERROR
        end_time = resource.getrusage(resource.RUSAGE_CHILDREN).ru_utime
        utime = end_time - start_time

        if redirected_stdin_file is not None:
            redirected_stdin_file.close()
        if redirected_stdout_file is not None:
            redirected_stdout_file.close()
        if redirected_stderr_file is not None:
            redirected_stderr_file.close()

        if use_valgrind:
            if valgrind_file is not None:
                sysio.write_file_contents(valgrind_file,
                                          temp_valgrind_log,
                                          logging_level=logging_level)
            sysio.write_message(valgrind_file, '\n\n')
            sysio.clean_file(temp_valgrind_log)

    return killed, utime, retcode
