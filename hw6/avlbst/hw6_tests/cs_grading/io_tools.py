import os
import cs_grading.logging_tools as log

####################################################################################################
# Purpose: Defining several strings that can be used for shorthand in many of the methods below.
# Definitions:
#      HEADER:      Contains a string used to print a header to a file.
#      FOOTER:      Contains a string used to print a footer to a file.
#      TEXT_EDITOR: Contains a string representing preferred text editor.
####################################################################################################
HEADER = '\n*++++++++++++++++++++++++++++++++++++++++++++++++*'
FOOTER = HEADER + '\n\n\n\n\n'
TEXT_EDITOR = 'subl'

####################################################################################################
# Purpose: Checks if a file exists
# Arguments:
#       file_name: The name of the file to check.
# Return Value:
#       The return value is either 0 or 1 depending on whether or not the file exists.
#       A 1 means the file exists and 0 means the file does not exist.
####################################################################################################
def exist_file(file_name):
    return os.path.isfile(file_name)

####################################################################################################
# Purpose: Checks if a directory exists
# Arguments:
#       dir_name: The name of the directory to check.
# Return Value:
#       The return value is either 0 or 1 depending on whether or not the dir exists.
#       A 1 means the dir exists and 0 means the dir does not exist.
####################################################################################################
def exist_dir(dir_name):
    return os.path.isdir(dir_name)

####################################################################################################
# Purpose: Used to copy files from src to dst.
# Arguments:
#       src:   The name of the source directory or file.
#       dst:   The name of the destination directory or file.
#       files: The name of the files to be copied. If left empty, will copy src.
####################################################################################################
def copy_file(src, dst, files=''):
    if files != '':
        files = '/' + files
    os.system('cp -r ' + src + files + ' ' + dst)

####################################################################################################
# Purpose: Used to move files from src to dst.
# Arguments:
#       src:   The name of the source directory or file.
#       dst:   The name of the destination directory or file.
#       files: The name of the files to be move. If left empty, will move src.
####################################################################################################
def move_file(src, dst, files=''):
    if files != '':
        files = '/' + files
    os.system('mv ' + src + files + ' ' + dst)

####################################################################################################
# Purpose: Used to create a directory.
# Arguments:
#       target: The name of the directory that will be created.
####################################################################################################
def mkdir(target, logging_level=log.LOGLEVEL_ERROR):
    if exist_dir(target):
        log.log_info('Directory {} already exists'.format(target), logging_level)
        return True
    elif exist_file(target):
        log.log_error('Expected file {} to be directory'.format(target), logging_level)
        return False

    log.log_info('Creating directory {}'.format(target), logging_level)
    os.mkdir(target)
    return True

####################################################################################################
# Purpose: Used to create an empty directory.
# Arguments:
#       target: The name of the directory that will be created.
####################################################################################################
def mkdir_empty(target, logging_level=log.LOGLEVEL_ERROR):
    if os.path.exists(target):
        if exist_dir(target):
            if os.listdir(target):
                remove_file(target + '/*')
            return True
        else:
            log.log_error('Expected file {} to be directory'.format(target), logging_level)
            return False
    else:
        return mkdir(target, logging_level=logging_level)

####################################################################################################
# Purpose: Used to create a directory. Also creates intermediate directories.
# Arguments:
#       target: The name of the directory that will be created.
####################################################################################################
def mkdir_recursive(target, logging_level=log.LOGLEVEL_ERROR):
    if exist_dir(target):
        log.log_info('Directory {} already exists'.format(target), logging_level)
        return True
    elif exist_file(target):
        log.log_error('Expected file {} to be directory'.format(target), logging_level)
        return False

    log.log_info('Creating directory {}'.format(target), logging_level)
    os.makedirs(os.path.abspath(target))
    return True

####################################################################################################
# Purpose: Checks for a file's existance and removes it if it exists.
# Arguments:
#       target_file: The name of the file to be removed.
####################################################################################################
def clean_file(target_file):
    if exist_file(target_file):
        remove_file(target_file)

####################################################################################################
# Purpose: Removes files from the current directory with a given name.
# Arguments:
#       file_name: The name of the file to be removed. Can be used to remove a single fine, or use
#                  the wildcard '*' to remove multiple files. For example, remove_file(*.txt) will
#                  remove all .txt files from the current directory. Multiple file names can be
#                  entered in a single string separated by a space.
####################################################################################################
def remove_file(file_name):
    files_to_remove = file_name.split()
    for remove in files_to_remove:
        os.system('rm ' + remove)

####################################################################################################
# Purpose: Removes empty directory from the current directory with a given name.
# Arguments:
#       dir_name: The name of the directory to be removed.
####################################################################################################
def remove_dir(dir_name):
    if exist_dir(dir_name):
        os.system('rm -r ' + dir_name)

####################################################################################################
# Purpose: Opens a file with a text editor for fast viewing.
# Arguments:
#       file_name:   The name of the file to be opened. Can be used to open a single file, or the
#                    wildcard '*' canbe used to open multiple files.
#       text_editor: The text editor that the file(s) will be opened with. By default, it is the
#                    text editordefined at the top of the file.
####################################################################################################
def open_file(file_name, text_editor=TEXT_EDITOR):
    os.system(text_editor + ' ' + file_name)

####################################################################################################
# Purpose: Write a header to a file, which is used to separate sections of a file.
# Arguments:
#       target_file: The file to which the header is written.
#       write_mode:  The mode in which the header is written. By default, it is appended to a file.
####################################################################################################
def write_header(target_file, write_mode='a'):
    with open(target_file, write_mode) as target:
        target.write(HEADER)

####################################################################################################
# Purpose: Write a footer to a file, which is used to separate sections of a file.
# Arguments:
#       target_file: The file to which the footer is written.
#       write_mode:  The mode in which the footer is written. By default, it is appended to a file.
####################################################################################################
def write_footer(target_file, write_mode='a'):
    with open(target_file, write_mode) as target:
        target.write(FOOTER)

####################################################################################################
# Purpose: Writes a message to a file.
# Arguments:
#       target_file: The file to which the message is written.
#       message:     The message that is written to the file.
#       write_mode:  The mode in which the message is written. By default, it is appended to a file.
####################################################################################################
def write_message(target_file, message, write_mode='a'):
    with open(target_file, write_mode) as target:
        target.write(message)

####################################################################################################
# Purpose: Writes the contents of one file to another file. Line endings are striped away so
#          leading/trailing white space is ignored.
# Arguments:
#       target_file: The name of the file to which the contents of the other file are written.
#       source_file: The name of the file from which the contents are extracted.
#       write_mode:  The mode in which the contents are written. By default, they are appended.
####################################################################################################
def write_file_contents(target_file,
                        source_file,
                        write_mode='a',
                        logging_level=log.LOGLEVEL_ERROR
                       ):
    if exist_file(source_file):
        target = open(target_file, write_mode)
        source = open(source_file, mode='r', errors='ignore')
        source_contents = source.read().strip()
        target.write(source_contents)
        target.close()
        source.close()
    else:
        log.log_error('Cannot find source file {}'.format(source_file), logging_level)

####################################################################################################
# Purpose: Reads the contents of a file and returns those contents.
# Arguments:
#       source_file: The name of the file that will be read.
####################################################################################################
def read_file_contents(source_file, logging_level=log.LOGLEVEL_ERROR):
    content = ''
    if exist_file(source_file):
        with open(source_file, mode='r', errors='ignore') as target:
            content = target.read()
    else:
        log.log_error('Cannot find source file {}'.format(source_file), logging_level)
    return content

####################################################################################################
# Purpose: Zip target directory.
# Arguments:
#       target:    The directory to be zipped.
#       file_name: Zip file name.
####################################################################################################
def zip_dir(target, file_name, logging_level=log.LOGLEVEL_ERROR):
    if not exist_dir(target):
        log.log_info('Directory {} does not exists'.format(target), logging_level)
    else:
        file_name = os.path.abspath(file_name)
        cwd = os.getcwd()
        os.chdir(target)
        os.system('zip ' + file_name + ' *')
        os.chdir(cwd)

####################################################################################################
# Purpose: Get relative path of path1 to path2.
####################################################################################################
def path_relative_to(path1, path2):
    absp1 = os.path.abspath(path1)
    absp2 = os.path.abspath(path2)
    prefix = os.path.commonprefix([absp1, absp2])
    relpath = os.path.relpath(path1, prefix)
    return relpath + '/'
