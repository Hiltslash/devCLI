#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char projname[100];
    if (argv[1] != NULL) {
    strcpy(projname, argv[1]);
    }
    else {
        strcpy(projname, "MYNEWPROJ");
    }
    printf("Project name is %s", projname);

    int result = mkdir(projname, 0755);
    if (result == 0) {
        printf("Directory '%s' created successfully.\n", projname);
    } else {
        perror("mkdir failed");
    }

    if (chdir(projname) != 0) {
        perror("chdir failed");
        return 1;
    }

    FILE *file = fopen("index.html", "w");
    if (file == NULL) {
        perror("Failed to create index.html");
        return 1;
    }

    fprintf(file, "<!DOCTYPE html>\n");
    fprintf(file, "<html>\n");
    fprintf(file, "    <head>\n");
    fprintf(file, "        <title></title>\n");
    fprintf(file, "        <link rel='stylesheet' href='style.css'>\n");
    fprintf(file, "        <meta charset='utf-8'>\n");
    fprintf(file, "    </head>\n");
    fprintf(file, "    <body>\n");
    fprintf(file, "        <script src='script.js'></script>\n");
    fprintf(file, "    </body>\n");
    fprintf(file, "</html>");
    fclose(file);
    printf("index.html created inside %s\n", projname);

    // Reuse the same variable for other files
    file = fopen("style.css", "w");
    if (file == NULL) {
        perror("Failed to create style.css");
        return 1;
    }
    fclose(file);

    file = fopen("script.js", "w");
    if (file == NULL) {
        perror("Failed to create script.js");
        return 1;
    }
    fclose(file);

    printf("style.css and script.js created.\n");
    return 0;
}
