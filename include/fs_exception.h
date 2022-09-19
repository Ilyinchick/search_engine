#pragma once

#include <exception>

class fs_exception : public std::exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class FileNotFoundException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class EmptyFileException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class NoConfigFieldException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class ConfigFieldIsEmptyException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class IncorrectVersionJsonException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class NoRequestsFieldException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class EmptyRequestsFieldException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class ConfigFilesException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class WriteToFileException : public fs_exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
