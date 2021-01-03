#include <iostream>
#include "vendor/clipp-master/include/clipp.h"
#include "include/FrontEnd.h"
#include "include/ServiceLoader.h"

typedef enum CommandCategory {
    kBuild,
    kHelp,
    kEmitIL,
    kCompileIL
} CommandCategory;

/// \param argc main function
/// \param argv main function
/// \return CommandCategory kBuild if nothing is matched;
CommandCategory parseCommandCategory(int argc, char* argv[]) {
    using namespace clipp;
    using namespace std;

    auto str = std::string(*argv);
    for (int i = 0; i < argc; ++i) {
        auto info = argv[i];
        auto param = std::string(info);
        std::cout << i << param << std::endl;
    }
    std::cout << "Hello, World!" << std::endl;
    std::cout << argc;

    bool f = true;
    string action;
    vector<string> actions;
    auto cli = (
            command("help"),
                    opt_value("command", action)
    );
    auto result = parse(argc, argv, cli);

    for(const auto& m : result.missing()) {
        cout << "missing " << m.param() << " after index " << m.after_index() << '\n';
    }
    return kBuild;
}

void frontend() {

};

void backend() {

}

void build() {

}

void generateIL() {

}

void compile() {

}

void help() {

}

void emitIL() {

}

int main(int argc, char* argv[]) {

    CommandCategory category = parseCommandCategory(argc, argv);

    switch (category) {
        case kHelp:
            help();
        case kBuild:
            build();
        case kCompileIL:
            compile();
        case kEmitIL:
            emitIL();
    }
    return 0;
}


