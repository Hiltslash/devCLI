#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void defaultProj(char *projname, char *scss) {
    FILE *file = fopen("main.lua", "w");
    if (file == NULL) {
        perror("Failed to create main.lua");
    }
    fprintf(file, "function love.load()\n");
    fprintf(file, "    love.window.setTitle('My Love2D Game')\n");
    fprintf(file, "    love.window.setMode(800, 600)\n");
    fprintf(file, "    -- Initialize game variables here\n");
    fprintf(file, "end\n\n");

    fprintf(file, "function love.update(dt)\n");
    fprintf(file, "    -- Update game logic here\n");
    fprintf(file, "    -- 'dt' is the time elapsed since the last frame\n");
    fprintf(file, "end\n\n");

    fprintf(file, "function love.draw()\n");
    fprintf(file, "    -- Draw everything here\n");
    fprintf(file, "    love.graphics.setColor(1, 1, 1)\n");
    fprintf(file, "    love.graphics.print('Hello, Love2D!', 350, 300)\n");
    fprintf(file, "end\n");
    fclose(file);
    printf("main.lua created inside %s\n", projname);
}

int main(int argc, char *argv[]) {
    char projname[100];
    char projtype[100] = "default";
    char scss[10] = "";

    if (argc >= 2) {
        strcpy(projname, argv[1]);
    } else {
        strcpy(projname, "NEWLOVE2DPROJ");
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
    }

    return 0;
}
