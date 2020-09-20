#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>


class FileException : public std::runtime_error {
public:
	FileException(std::string const& message) : std::runtime_error(message) {}
	virtual ~FileException() throw() {}
};

class MoveException : public std::runtime_error {
public:
    MoveException(std::string const& message): std::runtime_error(message) {}
	virtual ~MoveException() throw() {}
};

class CommandException : public std::runtime_error {
public:
    CommandException(std::string const& message): std::runtime_error(message) {}
	virtual ~CommandException() throw() {}
};

#endif
