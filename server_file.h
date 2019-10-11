#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <string>

class File {
    private:
    std::ifstream fi;

    public:
    explicit File(const std::string filename);
    std::istream& readLine(std::string *line);
    int error();
    ~File();
};

#endif
