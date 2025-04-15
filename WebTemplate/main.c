#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void defaultProj(char *projname, char *scss) {
    FILE *file = fopen("index.html", "w");
    if (file == NULL) {
        perror("Failed to create index.html");
    }
    if (strcmp(scss, "cred") == 0) {
        fprintf(file, "<!DOCTYPE html>\n");
        fprintf(file, "<html>\n");
        fprintf(file, "    <head>\n");
        fprintf(file, "        <title></title>\n");
        fprintf(file, "        <link rel='stylesheet' href='style.css'>\n");
        fprintf(file, "        <meta charset='utf-8'>\n");
        fprintf(file, "    </head>\n");
        fprintf(file, "    <body>\n");
        fprintf(file, "        <div id=\"top\" class=\"top\">\n");
        fprintf(file, "            <h1>Welcome!</h1>\n");
        fprintf(file, "        </div>\n");
        fprintf(file, "        <h3>Cool Features:</h3>\n");
        fprintf(file, "        <ol>\n");
        fprintf(file, "            <li>Stylish design</li>\n");
        fprintf(file, "            <li>Interactive elements</li>\n");
        fprintf(file, "            <li>Easy to customize</li>\n");
        fprintf(file, "        </ol>\n");
        fprintf(file, "        <p class=\"secret\">🕵️‍♀️ You found the secret!</p>\n");
        fprintf(file, "        <script src='script.js'></script>\n");
        fprintf(file, "    </body>\n");
        fprintf(file, "</html>\n");
        printf("chillred styling 👍");
    }
    else {
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
        fprintf(file, "</html>\n");
    }

    fclose(file);
    printf("index.html created inside %s\n", projname);

    file = fopen("style.css", "w");
    if (file == NULL) {
        perror("Failed to create style.css");
    }
    if (strcmp(scss, "cred") == 0) {
        fprintf(file, ".top {\n");
        fprintf(file, "    background: linear-gradient(to right, #ff7e5f, #feb47b);\n");
        fprintf(file, "    border-radius: 10px;\n");
        fprintf(file, "    text-align: center;\n");
        fprintf(file, "    justify-content: center;\n");
        fprintf(file, "    border-style: solid;\n");
        fprintf(file, "    padding: 10px 20px;\n");
        fprintf(file, "    border-width: 4px;\n");
        fprintf(file, "}\n");
        
        fprintf(file, "body {\n");
        fprintf(file, "    font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;\n");
        fprintf(file, "    background-color: rgb(255, 150, 12);\n");
        fprintf(file, "    text-align: center;\n");
        fprintf(file, "    justify-content: center;\n");
        fprintf(file, "}\n");
        
        fprintf(file, "button {\n");
        fprintf(file, "    border-radius: 10px;\n");
        fprintf(file, "    background: linear-gradient(to right, #89e017, #dbff0c);\n");
        fprintf(file, "    padding: 10px 20px;\n");
        fprintf(file, "}\n");
        
        fprintf(file, ".di {\n");
        fprintf(file, "    font-family: 'Courier New', Courier, monospace;\n");
        fprintf(file, "    font-weight: bold;\n");
        fprintf(file, "}\n");
        
        fprintf(file, ".secret {\n");
        fprintf(file, "    position: absolute;\n");
        fprintf(file, "    left: 3px;\n");
        fprintf(file, "    bottom: 3px;\n");
        fprintf(file, "}\n");
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
    fprintf(file, "</html>\n");
    fclose(file);
    printf("index.html (game) created inside %s\n", projname);

    file = fopen("style.css", "w");
    if (file == NULL) {
        perror("Failed to create style.css");
    }
    fprintf(file, "body {\n");
    fprintf(file, "    text-align: center;\n");
    fprintf(file, "    justify-content: center;\n");
    fprintf(file, "}\n");
    fprintf(file, "canvas {\n");
    fprintf(file, "    border: solid;\n");
    fprintf(file, "    border-width: 3px;\n");
    fprintf(file, "}\n");
    fclose(file);

    file = fopen("script.js", "w");
    if (file == NULL) {
        perror("Failed to create script.js (game)");
    }
    fprintf(file, "const gameCanvas = document.getElementById('gameCanvas');\n");
    fprintf(file, "const ctx = gameCanvas.getContext('2d');\n");
    fprintf(file, "function mainloop() {\n");
    fprintf(file, "    ctx.clearRect(0, 0, 800, 600);\n");
    fprintf(file, "    requestAnimationFrame(mainloop);\n");
    fprintf(file, "}\n");
    fprintf(file, "mainloop();\n");
    fclose(file);
    printf("style.css and script.js created. (game)\n");
}

int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";
    char scss[10] = "";

    if (argc >= 2) {
        strcpy(projname, argv[1]);
    } else {
        strcpy(projname, "MYNEWPROJ");
    }

    if (argc >= 3 && strcmp(argv[2], "-g") == 0) {
        strcpy(projtype, "canvasGame");
    }

    if (argc >= 3 && strcmp(argv[2], "-s") == 0) {
        if (argc >= 4) {
            if (strcmp(argv[3], "chillred") == 0) {
                strcpy(projtype, "default");
                strcpy(scss, "cred");
            }
        } else {
            fprintf(stderr, "Usage: webtemp -s <style>\n");
            exit(1);
        }
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
        defaultProj(projname, scss);
    } else if (strcmp(projtype, "canvasGame") == 0) {
        canvasGameProj(projname);
    }

    return 0;
}
