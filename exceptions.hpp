#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class IndexOutOfRangeException : public std::out_of_range {
public:
    explicit IndexOutOfRangeException(const std::string& msg)
        : std::out_of_range(msg) {}

    explicit IndexOutOfRangeException(int index, int size)
        : std::out_of_range("Индекс " + std::to_string(index) +
                           " вышел за пределы [0, " + std::to_string(size) + ")") {}
};

class EmptyContainerException : public std::runtime_error {
public:
    explicit EmptyContainerException(const std::string& msg)
        : std::runtime_error(msg) {}

    EmptyContainerException() : std::runtime_error("Контейнер пуст") {}
};

class InvalidArgumentException : public std::invalid_argument {
public:
    explicit InvalidArgumentException(const std::string& msg)
        : std::invalid_argument(msg) {}
};

#endif // EXCEPTIONS_HPP