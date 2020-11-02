import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log
import cs_grading.misc_tools as misc

####################################################################################################
# Purpose: Compares the contents of two files by looking for an extact line-by-line match. Each
#          line will be marked as either FOUND, EXTRA, or will show ACTUAL vs. EXPECTED.
# Arguments:
#      source_file:       The file containing solution contents.
#      comp_lines:        The file that is compared to the source_file.
#      write_file:        The file where the results are sent.
#      detailed_results:  Should detailed results be printed. Defaults to true.
#      logging_level:     Logging level.
#      kwargs:            See misc_tools.cleanup_lines more optinos.
# Return Value:
#      The return value is a tuple with three items:
#      1. The number of correct lines
#      2. The number of missing lines from comp
#      3. The number of extra lines beyond what was expected from source file
####################################################################################################
def compare_files(source_file,
                  comp_file,
                  write_file,
                  ordered_compare,
                  **kwargs
                 ):
    if kwargs is None:
        kwargs = dict()
    detailed_results = kwargs.get('detailed_results', True)
    logging_level = kwargs.get('logging_level', log.LOGLEVEL_ERROR)

    correct = -1
    missing = -1
    extra = -1

    if not sysio.exist_file(source_file):
        log.log_error('Source file {} not found'.format(source_file), logging_level)
    else:
        write = open(write_file, 'a')
        if not sysio.exist_file(comp_file):
            write.write('\n\tERROR: Compare file {} not found'.format(comp_file))
        else:
            source = open(source_file, mode='r', errors='ignore')
            comp = open(comp_file, mode='r', errors='ignore')
            source_lines = source.readlines()
            comp_lines = comp.readlines()
            source.close()
            comp.close()

            source_lines = misc.cleanup_lines(source_lines, **kwargs)
            comp_lines = misc.cleanup_lines(comp_lines, **kwargs)

            if ordered_compare:
                correct, missing, extra = compare_files_with_order(
                    source_lines,
                    comp_lines,
                    write,
                    detailed_results=detailed_results)
            else:
                correct, missing, extra = compare_files_without_order(
                    source_lines,
                    comp_lines,
                    write,
                    detailed_results=detailed_results)
        write.close()

    return correct, missing, extra

####################################################################################################
# Purpose: Compares the contents of two files by looking for an extact line-by-line match. Each
#          line will be marked as either FOUND, EXTRA, or will show ACTUAL vs. EXPECTED.
# Arguments:
#      source_lines:     The list of lines with the solution contents.
#      comp_lines:       The list of lines that are compared to the source_file
#      write:            The file object where the results are sent.
# Return Value:
#      The return value is a tuple with three items:
#      1. The number of correct lines
#      2. The number of missing lines from comp
#      3. The number of extra lines beyond what was expected from the source file
####################################################################################################
def compare_files_with_order(source_lines,
                             comp_lines,
                             write,
                             detailed_results=1
                            ):
    correct = 0
    missing = 0
    extra = 0

    # Counts missing lines and writes comparison results to file.
    for i, _ in enumerate(source_lines):
        if len(comp_lines) > i:
            if source_lines[i] == comp_lines[i]:
                if detailed_results:
                    write.write('\n\tFOUND: '    + source_lines[i])
                correct += 1
            else:
                if detailed_results:
                    write.write('\n\tEXPECTED: ' + source_lines[i])
                    write.write('\n\tACTUAL: ' + comp_lines[i])
                missing += 1
        else:
            if detailed_results:
                write.write('\nWARNING: Fewer lines in comp file than in source file.')
            for j in range(i, len(source_lines)):
                if detailed_results:
                    write.write('\n\tMISSING: ' + source_lines[j])
                missing += 1
            break

    # Counts extra lines and writes the results to file.
    for i in range(len(source_lines), len(comp_lines)):
        if detailed_results:
            write.write('\n\tEXTRA: ' + comp_lines[i])
        extra += 1

    # Returns list indicating number of missing and extra lines.
    return correct, missing, extra

####################################################################################################
# Purpose: Compares the contents of two files without requiring the lines of content be in the same
#          order for the files. Lines will be marked as either FOUND, MISSING, or EXTRA.
#          Duplicates are allowed.
# Arguments:
#      source_lines:     The list of lines with the solution contents.
#      comp_lines:       The list of lines that are compared to the source_file
#      write:            The file object where the results are sent.
# Return Value:
#      The return value is a tuple with three items:
#      1. The number of correct lines
#      2. The number of missing lines from comp
#      3. The number of extra lines beyond what was expected from the source file
####################################################################################################
def compare_files_without_order(source_lines,
                                comp_lines,
                                write,
                                detailed_results=1
                               ):
    correct = 0
    missing = 0
    extra = 0

    # Counts missing lines and writes comparison results to file. Order does not matter for this
    # operation.
    for i, _ in enumerate(source_lines):
        if source_lines[i] in comp_lines:
            if detailed_results:
                write.write('\n\tFOUND: ' + source_lines[i])
            correct += 1
        else:
            if detailed_results:
                write.write('\n\tMISSING: ' + source_lines[i])
            missing += 1

    # Returns list indicating number of missing and extra lines.
    for i, _ in enumerate(comp_lines):
        if comp_lines[i] not in source_lines:
            write.write('\n\tEXTRA: ' + comp_lines[i])
            extra += 1

    # Returns list indicating number of missing and extra lines.
    return correct, missing, extra
