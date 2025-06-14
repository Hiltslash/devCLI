#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void defaultProj(char *projname) {
    FILE *file = fopen("app.py", "w");
    if (file == NULL) {
        perror("Failed to create app.py");
    }
    fprintf(file, "from flask import Flask, render_template, url_for, request, redirect\napp = Flask(__name__)\n\nif __name__ == '__main__':\n    app.run(debug=True, port=5000)");
    printf("app.py created inside %s\n", projname);
    fclose(file);
}

int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";

    if (argc >= 2) {
        strcpy(projname, argv[1]);
    } else {
        strcpy(projname, "My Flask Website");
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
