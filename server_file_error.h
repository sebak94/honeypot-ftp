#ifndef __FILE_ERROR_H__
#define __FILE_ERROR_H__

#include <typeinfo>

#define BUF_LEN 256

class FileError: public std::exception {
    private:
    char error_msg[BUF_LEN];

    public:
    explicit FileError(const char* fmt, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~FileError() noexcept {}
};

#endif
