#include <exception/StorageException.h>

StorageException::StorageException(const char* message) : message(message) {
}

const char *StorageException::what() const noexcept {
    return message;
}
