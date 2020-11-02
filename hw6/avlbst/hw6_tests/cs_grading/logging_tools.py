####################################################################################################
# Purpose: Defining logging mode constants.
####################################################################################################
LOGLEVEL_NONE = 0
LOGLEVEL_ERROR = 1
LOGLEVEL_WARNING = 2
LOGLEVEL_INFO = 3


def log_error(text, logging_level):
    if logging_level >= LOGLEVEL_ERROR:
        print('ERROR:    ', text)


def log_warning(text, logging_level):
    if logging_level >= LOGLEVEL_WARNING:
        print('WARNING:  ', text)


def log_info(text, logging_level):
    if logging_level >= LOGLEVEL_INFO:
        print('INFO:     ', text)
