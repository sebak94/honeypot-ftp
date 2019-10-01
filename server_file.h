#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <string>

class File {
    private:
    std::ifstream fi;

    public:
    explicit File(const std::string filename);
    std::istream& readLine(char *buf, size_t length);
    int error();
    ~File();
};

#endif
