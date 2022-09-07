#include "fs_exception.h"

const char *fs_exception::what() const noexcept {
    return "File system exception";
}

const char *FileNotFoundException::what() const noexcept {
    return "File not found";
}

const char *EmptyFileException::what() const noexcept {
    return "File is empty";
}

const char *NoConfigFieldException::what() const noexcept {
    return "No \"config\" field";
}

const char *ConfigFieldIsEmptyException::what() const noexcept {
    return "\"Config\" field is empty";
}

const char *IncorrectVersionJsonException::what() const noexcept {
    return "Incorrect version in JSON config file";
}

const char *NoRequestsFieldException::what() const noexcept {
    return "No \"requests\" field in requests.json";
}

const char *EmptyRequestsFieldException::what() const noexcept {
    return "\"requests\" field is emtpy";
}
