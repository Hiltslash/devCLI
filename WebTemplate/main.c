#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
void defaultProj(char *projname) {
    FILE *file = fopen("index.html", "w");
    if (file == NULL) {
        perror("Failed to create index.html");
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
    }
    fclose(file);

    file = fopen("script.js", "w");
    if (file == NULL) {
        perror("Failed to create script.js");
    }
    fclose(file);

    printf("style.css and script.js created.\n");
}

void canvasGameProj(char *projname) {
    FILE *file = fopen("index.html", "w");
    if (file == NULL) {
        perror("Failed to create index.html");
    }

    fprintf(file, "<!DOCTYPE html>\n");
    fprintf(file, "<html>\n");
    fprintf(file, "    <head>\n");
    fprintf(file, "        <title></title>\n");
    fprintf(file, "        <link rel='stylesheet' href='style.css'>\n");
    fprintf(file, "        <meta charset='utf-8'>\n");
    fprintf(file, "    </head>\n");
    fprintf(file, "    <body>\n");
    fprintf(file, "        <canvas width='800' height='600' id='gameCanvas'>canvas unsupported</canvas>\n");
    fprintf(file, "        <script src='script.js'></script>\n");
    fprintf(file, "    </body>\n");
    fprintf(file, "</html>");
    fclose(file);
    printf("index.html (game) created inside %s\n", projname);

    // Reuse the same variable for other files
    file = fopen("style.css", "w");
    if (file == NULL) {
        perror("Failed to create style.css");
    }
    fprintf(file, "body {\n");
    fprintf(file, "    text-align: center;\n");
    fprintf(file, "    justify-content: center;\n");
    fprintf(file, "}");
    fprintf(file, "canvas {\n");
    fprintf(file, "    border: solid;\n");
    fprintf(file, "    border-width: 3px;\n");
    fprintf(file, "}");
    fclose(file);

    file = fopen("script.js", "w");
    if (file == NULL) {
        perror("Failed to create script.js (game)");
    }
    fprintf(file, "const gameCanvas = document.getElementById('gameCanvas')\n");
    fprintf(file, "const ctx = gameCanvas.getContext('2d')\n");
    fprintf(file, "function mainloop() {\n");
    fprintf(file, "    ctx.clearRect(0,0,800,600)\n");
    fprintf(file, "    requestAnimationFrame(mainloop)\n");
    fprintf(file, "}\n");
    fprintf(file, "mainloop()");

    fclose(file);
    printf("style.css and script.js created. (game)\n");
}

int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";
    if (argv[1] != NULL) {
    strcpy(projname, argv[1]);
    }
    else {
        strcpy(projname, "MYNEWPROJ");
    }
    if (argv[2] != NULL && strcmp("-g", argv[2]) == 0) {
        strcpy(projtype, "canvasGame");
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
    }

    if (strcmp(projtype, "default") == 0) {
        defaultProj(projname);
    }
    else if (strcmp(projtype, "canvasGame") == 0){
        canvasGameProj(projname);
    }
}
