from configparser import ConfigParser
import csv
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log
import cs_grading.misc_tools as misc
import cs_grading.result_tools as res

RUBRIC_SECT_WARNING = 'warning'
RUBRIC_SECT_VALGRIND = 'valgrind'
RUBRIC_SECT_TEST = 'test'
RUBRIC_SECT_OTHER = 'other'
RUBRIC_SECT_ALL = [
    RUBRIC_SECT_WARNING,
    RUBRIC_SECT_VALGRIND,
    RUBRIC_SECT_TEST,
    RUBRIC_SECT_OTHER,
]

RUBRIC_WARNING_LIMIT = 'warning_limit'
RUBRIC_WARNING_BRNORET = 'warning_br_no_ret'
RUBRIC_WARNING_RTOP = 'warning_rt_op_neff'
RUBRIC_WARNING_ASSIGN = 'warning_assign_truth'
RUBRIC_WARNING_UNINI = 'warning_uninit_value'
RUBRIC_WARNING_COMPS = 'warning_comp_sign'
RUBRIC_WARNING_UNUSED = 'warning_unused_var'
RUBRIC_WARNING_RESULT = {
    res.CWARNING_BRNORET: RUBRIC_WARNING_BRNORET,
    res.CWARNING_RTOP:    RUBRIC_WARNING_RTOP,
    res.CWARNING_ASSIGN:  RUBRIC_WARNING_ASSIGN,
    res.CWARNING_UNINIT:  RUBRIC_WARNING_UNINI,
    res.CWARNING_COMPS:   RUBRIC_WARNING_COMPS,
    res.CWARNING_UNUSED:  RUBRIC_WARNING_UNUSED,
}

RUBRIC_VALGRIND_LIMIT = 'valgrind_limit'
RUBRIC_VALGRIND_FLAT = 'valgrind_flat'
RUBRIC_VALGRIND_PTEST = 'valgrind_per_test'

RUBRIC_OTHER_POINT = 'point'
RUBRIC_OTHER_COMMENT = 'commment'

def load_config(config, config_file, logging_level=log.LOGLEVEL_ERROR):
    if not sysio.exist_file(config_file):
        log.log_warning('Rubric file {} not found'.format(config_file), logging_level)
    else:
        config.read(config_file)

def load_rubric(rubric_file, rubric=None, logging_level=log.LOGLEVEL_ERROR):
    config = ConfigParser()
    if rubric is not None:
        config.read_dict(rubric)
    load_config(config, rubric_file, logging_level=logging_level)
    for sect in RUBRIC_SECT_ALL:
        if not config.has_section(sect):
            config.add_section(sect)

    return config

def load_other_rubric(rubric_file, logging_level=log.LOGLEVEL_ERROR):
    deduct = list()
    if not sysio.exist_file(rubric_file):
        log.log_warning('Rubric file {} not found'.format(rubric_file), logging_level)
    else:
        with open(rubric_file, 'r') as rfile:
            rubric_reader = csv.reader(rfile, delimiter='\t')
            for deduct_row in rubric_reader:
                if len(deduct_row) != 2:
                    log.log_error(
                        "Row should have two columns: " + str(deduct_row),
                        logging_level)
                elif not misc.is_num(deduct_row[0].strip()):
                    log.log_error(
                        "First column needs to be number: " + str(deduct_row),
                        logging_level)
                else:
                    deduct.append({
                        RUBRIC_OTHER_POINT: float(deduct_row[0].strip()),
                        RUBRIC_OTHER_COMMENT: deduct_row[1].strip()})
    return deduct

def get_warning_deduction_limit(rubric):
    return rubric.getfloat(RUBRIC_SECT_WARNING, RUBRIC_WARNING_LIMIT, fallback=-1)

def get_warning_deduction(rubric, warning):
    rubric_code = RUBRIC_WARNING_RESULT.get(warning, '')
    return rubric.getfloat(RUBRIC_SECT_WARNING, rubric_code, fallback=0)

def get_valgrind_deduction_limit(rubric):
    return rubric.getfloat(RUBRIC_SECT_VALGRIND, RUBRIC_VALGRIND_LIMIT, fallback=-1)

def get_valgrind_deduction(rubric, failed_count):
    flat = rubric.getfloat(RUBRIC_SECT_VALGRIND, RUBRIC_VALGRIND_FLAT, fallback=0)
    ptest = rubric.getfloat(RUBRIC_SECT_VALGRIND, RUBRIC_VALGRIND_PTEST, fallback=0)
    return flat + ptest * failed_count

def get_test_deduction(rubric, test_name):
    return rubric.getfloat(RUBRIC_SECT_TEST, test_name, fallback=0)

def get_other_deduction(rubric, name):
    return rubric.getfloat(RUBRIC_SECT_OTHER, name, fallback=0)
