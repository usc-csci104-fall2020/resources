import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log
import cs_grading.misc_tools as misc

CFG_SECT_INFO = 'info'
CFG_SECT_GRADER = 'grader'
CFG_SECT_SRC = 'source'
CFG_SECT_DST = 'destination'
CFG_SECT_ZIP = 'zip'
CFG_SECT_MASTER = 'master'

CFG_INTERP_HW = 'hw'
CFG_INTERP_STUDENT = 'student'

def set_homework(config, homework):
    config[CFG_SECT_INFO][CFG_INTERP_HW] = homework

def set_student(config, student):
    config[CFG_SECT_INFO][CFG_INTERP_STUDENT] = student

def get_student_list(config):
    return config.get(CFG_SECT_INFO, 'student_list')

def read_student_list(config, logging_level=log.LOGLEVEL_ERROR):
    student_list = get_student_list(config)
    students = list()
    if not sysio.exist_file(student_list):
        log.log_error(
            'Cannot open student list ' + student_list,
            logging_level)
        return students

    with open(student_list, 'r') as student_file:
        students = student_file.readlines()
        students = misc.cleanup_lines(students, skip_white_space=True)
    return students

def get_grader_name(config):
    return config.get(CFG_SECT_GRADER, 'name')

def get_grader_usc_username(config):
    return config.get(CFG_SECT_GRADER, 'usc_username')

def get_grader_github_username(config):
    return config.get(CFG_SECT_GRADER, 'github_username')

def get_grader_report_string(config):
    return config.get(CFG_SECT_GRADER, 'report_string')

def get_grader_report_info(config):
    return config.get(CFG_SECT_GRADER, 'report_info')

def get_src_student_submission(config):
    return config.get(CFG_SECT_SRC, 'student_submission')

def get_src_grading_script(config):
    return config.get(CFG_SECT_SRC, 'grading_script')

def get_src_grade_report(config):
    return config.get(CFG_SECT_SRC, 'grade_report')

def get_dst_student_submission(config):
    return config.get(CFG_SECT_DST, 'student_submission')

def get_dst_grading_script(config):
    return config.get(CFG_SECT_DST, 'grading_script')

def get_dst_grade_report(config):
    return config.get(CFG_SECT_DST, 'grade_report')

def get_dst_grader_info(config):
    return config.get(CFG_SECT_DST, 'grader_info')

def get_dst_rubric_other(config):
    return config.get(CFG_SECT_DST, 'rubric_other')

def get_zipfile_dir(config):
    return config.get(CFG_SECT_ZIP, 'zipfile_dir')

def get_zipfile_name(config):
    return config.get(CFG_SECT_ZIP, 'zipfile_name')

def get_grader_github_info(config):
    return config.get(CFG_SECT_MASTER, 'grader_github')

def get_grader_assignment_info(config):
    return config.get(CFG_SECT_MASTER, 'grader_assignment')

def get_rubric_other(config):
    return config.get(CFG_SECT_MASTER, 'rubric_other')

def get_grade_file(config):
    return config.get(CFG_SECT_MASTER, 'grade_file')

def get_log_dir(config):
    return config.get(CFG_SECT_MASTER, 'log_dir')

def get_log_file(config):
    return config.get(CFG_SECT_MASTER, 'log_file')
