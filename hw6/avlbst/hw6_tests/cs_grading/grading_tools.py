import io
import cs_grading.executable_tools as exe
import cs_grading.io_tools as sysio
import cs_grading.logging_tools as log
import cs_grading.markdown_tools as md
import cs_grading.result_tools as res
import cs_grading.rubric_tools as rb

####################################################################################################
# Purpose: Defining several constants that can be used for shorthand in many of the methods below.
####################################################################################################
GRHLEVEL_TITLE = 2
GRHLEVEL_PROBLEM = 3
GRHLEVEL_OTHER = 4
GRFOOTER = """
If you wish to dispute any matters regarding your score on this assignment, please submit a regrade request using this [form](https://docs.google.com/forms/d/e/1FAIpQLSeOcq7ssGUgHvPR2X2dhdEarux5d9ju_9IXr5c5biksM_iW8g/viewform). Any and all discussions pertaining to your homework score **must** be done via comments on this issue once a grader has been assigned to your case.  Do not use email to discuss grading matters as they won't be considered part of the regrade process.

You have 7 days from the time this issue was posted to *raise* a dispute about any grading issues. Allow up to 48 hours for your grader to respond. If your grader cannot resolve the issue within 7 days, you must elevate the issue to one of the TAs by attending their office hours. If after an additional 7 days you are still unhappy with the grading result, you must elevate the issue to Professor Redekopp or Professor Batista within 3 days. Your professor will have the final input. 

This means you have a maximum of 7 + 7 + 3 days to resolve all grading disputes, after which point all grades are final. 

You are expected to follow the _Grading Disputes_ policies outlined on the [assignments](http://bits.usc.edu/cs104/assignments) page."""

####################################################################################################
# Purpose: Grader information.
# Arguments:
#     name:    The grader's name.
#     github:  The grader's GitHub id.
####################################################################################################
class Grader:
    def __init__(self, grader_info=None, logging_level=log.LOGLEVEL_ERROR):
        self.name = 'Grader-name'
        self.github = 'grader-github-ID'
        if grader_info is not None:
            self.load_grader_info(grader_info, logging_level)

    def load_grader_info(self, grader_info, logging_level=log.LOGLEVEL_ERROR):
        if sysio.exist_file(grader_info):
            grader_file = open(grader_info, mode='r', errors='ignore')
            lines = grader_file.readlines()
            grader_file.close()
            if len(lines) < 2:
                log.log_error(
                    'Grader info needs 2 lines but found {}'.format(str(len(lines))),
                    logging_level
                    )
            else:
                if len(lines) > 2:
                    log.log_warning(
                        'Grader info needs 2 lines but found {}'.format(str(len(lines))),
                        logging_level
                    )
                self.name = lines[0].strip()
                self.github = lines[1].strip()
        else:
            log.log_error('Grader info file {} not found'.format(grader_info), logging_level)

    def get_grader_info(self):
        return '{name} (@{github})'.format(name=self.name, github=self.github)

####################################################################################################
# Purpose: Breakdown of homework grading.
# Arguments:
#     number:  The homework number.
####################################################################################################
class Homework:
    def __init__(self,
                 number,
                 result_dir,
                 remove_output,
                 detailed_results=True,
                 compile_flags=exe.CPPFLAGS,
                 logging_level=log.LOGLEVEL_ERROR
                ):
        self.number = number
        self.result_dir = result_dir
        self.remove_output = remove_output
        self.detailed_results = detailed_results
        self.compile_flags = compile_flags
        self.logging_level = logging_level

        self.total_points = 0
        self.total_max = 0
        self.total_other = 0
        self.problems = []
        self.other_deductions = []
        self.problem_subtotal = []

        sysio.mkdir(self.result_dir, logging_level=self.logging_level)


    def add_problem(self, problem):
        self.problems.append(problem)


    def _add_other_deduction(self, points, comment):
        self.other_deductions.append((points, comment))


    def grade_other_deduction(self, other_rubric):
        other_deduct = rb.load_other_rubric(other_rubric, self.logging_level)
        for deduct in other_deduct:
            self._add_other_deduction(
                deduct[rb.RUBRIC_OTHER_POINT],
                deduct[rb.RUBRIC_OTHER_COMMENT])


    def write_score_breakdown(self, report_file):
        report_stream = io.StringIO()
        for problem in self.problems:
            problem.write_score_breakdown(report_stream)
            points = problem.get_test_points()
            self.total_points += points
            self.total_max += problem.test_max
            self.problem_subtotal.append(str(round(points, 2)))

        md.write_header(report_stream, 'Other Deductions & Penalties:', GRHLEVEL_PROBLEM)
        for deduct in self.other_deductions:
            self.total_other += deduct[0]
            self.total_points -= deduct[0]
            deduction_text = '(-{pt} points) {comment}'.format(
                pt=round(deduct[0], 2),
                comment=deduct[1])
            md.write_list(report_stream, deduction_text)
        if self.other_deductions:
            md.end_list(report_stream)

        self.total_points = max(self.total_points, 0)
        self._write_score_calculation(report_stream)

        summary_text = 'I have completely finished grading your'
        summary_text += ' HW {num:02d} test cases and you received'.format(num=self.number)
        summary_text += ' **{total}/{max} points**.'.format(
            total=round(self.total_points, 2),
            max=round(self.total_max, 2))
        breakdown_text = 'This is the score breakdown:'
        md.write_paragraph(report_file, summary_text)
        md.write_paragraph(report_file, breakdown_text)
        md.write_paragraph(report_file, report_stream.getvalue().strip())
        report_stream.close()


    def _write_score_calculation(self, report_file):
        md.write_header(report_file, 'Total Score:', GRHLEVEL_PROBLEM)
        calc = '({test}) - ({other}) = **{total:}/{max} points**'.format(
            test=' + '.join(self.problem_subtotal),
            other=self.total_other,
            total=round(self.total_points, 2),
            max=round(self.total_max, 2))
        md.write_list(report_file, calc)
        md.end_list(report_file)

####################################################################################################
# Purpose: Breakdown of homework grading.
# Arguments:
#     number:    The problem number.
#     nams:      The problem name.
#     test_max:  The max number of points.
####################################################################################################
class Problem:
    def __init__(self, homework, number, name, test_max):
        homework.add_problem(self)
        self.result_dir = homework.result_dir
        self.remove_output = homework.remove_output
        self.detailed_results = homework.detailed_results
        self.compile_flags = homework.compile_flags
        self.logging_level = homework.logging_level

        self.number = number
        self.name = name
        self.test_max = test_max
        self.test_count = 0
        self.test_deductions = []
        self.test_points = None
        self.valgrind_error = 0

        self.compile_file = self.result_dir + '/' + self.name + '_compile.txt'
        self.result_file = self.result_dir + '/' + self.name + '_result.txt'
        self.valgrind_file = self.result_dir + '/' + self.name + '_valgrind.txt'
        self.formatted_file = self.result_dir + '/' + self.name + '_formatted.txt'
        sysio.clean_file(self.compile_file)
        sysio.clean_file(self.result_file)
        sysio.clean_file(self.valgrind_file)
        sysio.clean_file(self.formatted_file)

        self.use_valgrind = None
        self.timeout = None
        self.rubric = dict()


    def generate_results(self,
                         grading,
                         use_valgrind,
                         timeout=None,
                        ):
        self.use_valgrind = use_valgrind
        self.timeout = timeout

        return grading(self)


    def open_result(self, text_editor=sysio.TEXT_EDITOR):
        if sysio.exist_file(self.result_file):
            sysio.open_file(self.result_file, text_editor)
        if sysio.exist_file(self.valgrind_file):
            sysio.open_file(self.valgrind_file, text_editor)


    def grade_problem(self, general_rubric=None, problem_rubric=None):
        if not self._results_generated():
            log.log_error(
                'Grading problem {} before results are generated'.format(self.name),
                self.logging_level)
        else:
            if general_rubric is not None:
                self.rubric = rb.load_rubric(
                    general_rubric,
                    self.rubric,
                    logging_level=self.logging_level)
            if problem_rubric is not None:
                self.rubric = rb.load_rubric(
                    problem_rubric,
                    self.rubric,
                    logging_level=self.logging_level)

            # check that rubric adds up to the correct point value
            pointsum = 0
            for testname in self.rubric[rb.RUBRIC_SECT_TEST]:
                pointsum = pointsum + self.rubric.getfloat(rb.RUBRIC_SECT_TEST, testname, fallback=0)

            if abs(pointsum - self.test_max) < .001:
                log.log_info("Sum of all points in rubric: %.02f" % pointsum, self.logging_level)
            else:
                log.log_error("Total point values in rubric (%.02f) DO NOT MATCH score assigned to problem (%d)!" % (pointsum, self.test_max), self.logging_level)

            self._grade_compile_result()
            self.test_count = self._grade_test_result()
            self._grade_valgrind_result()


    def _grade_compile_result(self):
        compile_max = rb.get_warning_deduction_limit(self.rubric)
        compile_total = compile_max
        warnings = res.read_compile_result(self.compile_file, logging_level=self.logging_level)
        for warning in warnings:
            deduction = rb.get_warning_deduction(self.rubric, warning)
            if deduction <= compile_total or compile_max < 0:
                self._add_deduction(
                    deduction,
                    'Warning {}'.format(
                        res.CWARNING_OUTPUT.get(warning, ''))
                    )
                compile_total -= deduction
            else:
                self._add_deduction(
                    compile_total,
                    'Warning {} (should be -{} but warning deduction capped at -{})'.format(
                        res.CWARNING_OUTPUT.get(warning, ''),
                        deduction,
                        compile_max),
                    )
                compile_total = 0


    def _grade_test_result(self):
        test_names = res.read_formatted_result(
            self.formatted_file,
            logging_level=self.logging_level)
        for test_name, result, vresult in test_names:
            if result != res.ERESULT_PASS:
                self._add_deduction(
                    rb.get_test_deduction(self.rubric, test_name),
                    'Test {} {}'.format(test_name, res.ERESULT_OUTPUT.get(result, ''))
                    )
            if vresult == res.VRESULT_FAIL:
                self._add_valgrind_deduction()
        return len(test_names)


    def _add_valgrind_deduction(self):
        self.valgrind_error += 1


    def _grade_valgrind_result(self):
        if self.valgrind_error > 0:
            valgrind_max = rb.get_valgrind_deduction_limit(self.rubric)
            deduction = rb.get_valgrind_deduction(self.rubric, self.valgrind_error)
            if deduction <= valgrind_max or valgrind_max < 0:
                self._add_deduction(
                    rb.get_valgrind_deduction(self.rubric, self.valgrind_error),
                    'Valgrind error')
            else:
                self._add_deduction(
                    valgrind_max,
                    'Valgrind error (should be -{} but valgrind deduction capped at -{})'.format(
                        deduction,
                        valgrind_max),
                    )


    def _results_generated(self):
        return (self.compile_file is not None
                and self.result_file is not None
                and self.valgrind_file is not None
                and self.formatted_file is not None)


    def _add_deduction(self, points, comment):
        self.test_deductions.append((points, comment))


    def get_test_points(self):
        if self.test_points is None:
            total = 0
            for deduct in self.test_deductions:
                total += deduct[0]
            self.test_points = max(0, self.test_max - total)
        return self.test_points


    def write_score_breakdown(self, ostream):
        self.test_points = self.get_test_points()
        problem_title = 'Problem {num} ({name}) ({pt}/{total}):'.format(
            num=self.number,
            name=self.name,
            pt=round(self.test_points, 2),
            total=round(self.test_max, 2))
        md.write_header(ostream, problem_title, GRHLEVEL_PROBLEM)

        for deduct in self.test_deductions:
            deduction_text = '(-{pt} points) {comment}'.format(
                pt=round(deduct[0], 2),
                comment=deduct[1])
            md.write_list(ostream, deduction_text)
        if self.test_deductions:
            md.end_list(ostream)

####################################################################################################
# Purpose: Generate grade report for homework.
# Arguments:
#     homework:    Homework instance.
#     grader:      Grader information.
#     report_dir:  Directory where report is generated.
#     overwrite:   If grade report already exist, should it be overwritten.
####################################################################################################
def generate_grade_report(homework,
                          grader,
                          report_dir,
                          overwrite=False,
                          logging_level=log.LOGLEVEL_ERROR
                         ):
    report_filename = report_dir + 'GR{}_hw-username.md'.format(str(homework.number))
    if sysio.exist_file(report_filename):
        if not overwrite:
            log.log_error('Report {} already exists'.format(report_filename), logging_level)
            return
        else:
            log.log_warning('Overwriting existing report {}'.format(report_filename), logging_level)

    report_file = open(report_filename, mode='w')
    title = 'HW {num:02d} Test Case Grade Report'.format(num=homework.number)
    md.write_header(report_file, title, GRHLEVEL_TITLE)
    homework.write_score_breakdown(report_file)
    md.write_paragraph(report_file, GRFOOTER)
    report_file.close()
