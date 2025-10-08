#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void defaultProj(char *projname) {
    FILE *file = fopen("main.c", "w");
    if (file == NULL) {
        perror("Failed to create main.c");
    } else {
        fprintf(file,
            "#include <stdio.h>\n#include <unistd.h>\n#include <string.h>\n#include <stdlib.h>"
            "\n\nint main() {\n\n}");
        fclose(file);
        printf("main.c created inside %s\n", projname);
    }

}


int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";

    if (argc >= 2) {
        strcpy(projname, argv[1]);
    } else {
        strcpy(projname, "My C Project");
    }



    printf("Project name is %s\n", projname);

    int result = mkdir(projname, 0755);
    if (result == 0) {
        printf("Directory '%s' created successfully.\n", projname);
    } else {
        perror("mkdir failed");
    }

    if (chdir(projname) != 0) {
        perror("chdir failed");
    }

    if (strcmp(projtype, "default") == 0) {
        defaultProj(projname);
    }

    return 0;
}
