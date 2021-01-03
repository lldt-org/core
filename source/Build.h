//
// Created by User on 1/3/2021.
//

#ifndef LLDT_CORE_BUILD_H
#define LLDT_CORE_BUILD_H

#include <dlfcn.h>
#include <string>
#include <vector>


typedef struct Optimization {
    const char* name;
    uint8_t level;
} Optimization;

struct Config {
    std::vector<std::string> Optimization;
};



class Build {

    Build(std::string path, std::string frontend) {
    }

    int compile() {

    }

private:
    void loadLib(const char *file) {

        void* handle = dlopen(file, RTLD_LAZY);
    }
};


#endif //LLDT_CORE_BUILD_H
