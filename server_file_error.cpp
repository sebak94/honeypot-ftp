#include "server_file_error.h"
#include <errno.h>
#include <cstdio>
#include <cstdarg>
#include <string.h>

FileError::FileError(const char* fmt, ...) noexcept {
    int _errno = errno;
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(error_msg, BUF_LEN, fmt, args);
    va_end(args);
    strncpy(error_msg + s, strerror(_errno), BUF_LEN - s);
    error_msg[BUF_LEN - 1] = 0;
}

const char* FileError::what() const noexcept {
    return error_msg;
}
