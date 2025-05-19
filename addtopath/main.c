#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <path_to_add> <name>\n", argv[0]);
        return 1;
    }

    const char *path_to_add = argv[1];
    const char *name = argv[2];

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/.zshrc", getenv("HOME"));

    FILE *file = fopen(full_path, "a");
    if (file == NULL) {
        perror("Failed to open .zshrc");
        return 1;
    }

    fprintf(file, "\nalias %s=\"%s\"\n", name, path_to_add);

    fclose(file);
    system("source ~/.zshrc");
    printf("Added command/script to zshrc.");
    return 0;
}
