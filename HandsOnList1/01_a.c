#include <unistd.h>  // for symlink()
#include <stdio.h>   // for printf(), perror()

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <link_name>\n", argv[0]);
        return 1;
    }

    const char *source = argv[1];
    const char *target = argv[2];

    if (symlink(source, target) == -1) {
        perror("symlink");
        return 1;
    }

    printf("Symbolic link created: %s -> %s\n", target, source);
    return 0;
}
