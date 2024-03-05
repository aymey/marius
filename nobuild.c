// TODO: make build directory

#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-pedantic"

void marius_src(const char *src) {
    Cstr src_path = PATH("src", src);
#ifndef _WIN32
    CMD("cc", CFLAGS, "-o", "build/marius", src_path);
#else
    CMD("cl.exe", "/Fe.\\tools\\", tool_path);
#endif
}

void marius_srcs(void) {
    FOREACH_FILE_IN_DIR(src, "src", {
        if (ENDS_WITH(src, ".c")) {
            marius_src(src);
        }
    });
}

void print_chain(const Chain *chain) {
    INFO("input: %s", chain->input_filepath);
    INFO("output: %s", chain->output_filepath);
    FOREACH_ARRAY(Cmd, cmd, chain->cmds, {
        INFO("cmd: %s", cmd_show(*cmd));
    });
}

int main(int argc, char **argv) {
    GO_REBUILD_URSELF(argc, argv);

    marius_srcs();

    return 0;
}
