#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <string>

class Directory {
    private:
    const std::string name;

    public:
    explicit Directory(const std::string name);
    std::string getName() const;
    bool operator==(const Directory &d) const;
    bool operator<(const Directory &rd) const;
    ~Directory();
};

#endif
