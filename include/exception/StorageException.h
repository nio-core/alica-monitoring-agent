#pragma once

#include <exception>

class StorageException : public std::exception {
public:
    explicit StorageException(const char *string);

    const char* what() const noexcept override;

private:
    const char* message;
};
