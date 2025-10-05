#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void defaultProj(char *projname) {
    FILE *file = fopen("main.py", "w");
    if (file == NULL) {
        perror("Failed to create main.py");
    } else {
        fprintf(file,
            "from time import sleep\nimport os\nimport random\nfrom random import randint\n"
            "def clear(): os.system('cls' if os.name == 'nt' else 'clear')\n");
        fclose(file);
        printf("main.py created inside %s\n", projname);
    }

    // Run the external program
    char *argv[] = {"/Users/beaudavidson/codingprojects/github/devcli/autovenv/runme1.0", "vnv", NULL};
    execv("/Users/beaudavidson/codingprojects/github/devcli/autovenv/runme1.0", argv);

    // Only reached if execv fails
    perror("execv failed");
    exit(1);
}


int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";

    if (argc >= 2) {
        strcpy(projname, argv[1]);
    } else {
        strcpy(projname, "My Python Project");
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
