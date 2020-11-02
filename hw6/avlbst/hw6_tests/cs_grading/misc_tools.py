####################################################################################################
# Purpose: Clean up lines before comparison.
# Arguments:
#      source_lines:     The lines to be cleaned.
#      starting_line:    An optional argument to start comparison from a particular line. Default
#                        is the beginning.
#      skip_white_space: An optional argument to filter out white space from both the source and
#                        comp files.
#      ignore_leading_characters: An optional argument to ignore the first n characters.
#      ignore_lines_with: An optional argument to ignore lines that contain this sequence.
####################################################################################################
def cleanup_lines(source_lines, **kwargs):
    if kwargs is None:
        kwargs = dict()
    starting_line = kwargs.get('starting_line', 0)
    skip_white_space = kwargs.get('skip_white_space', None)
    ignore_leading_characters = kwargs.get('ignore_leading_characters', 0)
    ignore_lines_with = kwargs.get('ignore_lines_with', None)

    if skip_white_space:
        source_lines = [x.strip() for x in source_lines]

    source_lines = [x[ignore_leading_characters:] for x in source_lines]

    if ignore_lines_with != None:
        source_lines = [item for item in source_lines if ignore_lines_with not in item]

    source_lines = remove_values_from_list(source_lines, '')
    source_lines = source_lines[starting_line:]

    return source_lines

####################################################################################################
# Purpose: Removes all instances of a given value from a list.
# Arguments:
#       rlist: The original list.
#       value: The single value that is to be removed from the list.
# Return Value:
#       The return value is a list with the contents of the original list, minus the value. The
#       order of elements in the list is stable.
####################################################################################################
def remove_values_from_list(rlist, value):
    return [item for item in rlist if item != value]

####################################################################################################
# Purpose: Check if a string is an integer.
####################################################################################################
def is_int(num):
    try:
        int(num)
        return True
    except ValueError:
        return False

####################################################################################################
# Purpose: Check if a string is a number.
####################################################################################################
def is_num(num):
    try:
        float(num)
        return True
    except ValueError:
        return False
