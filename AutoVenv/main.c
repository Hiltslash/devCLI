#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char vname[100];

    // Set venv name
    if (argc > 1) {
        strncpy(vname, argv[1], sizeof(vname) - 1);
        vname[sizeof(vname) - 1] = '\0'; // Ensure null-termination
    } else {
        strcpy(vname, "new-venv");
    }

    // Create the venv
    char command[200];
    snprintf(command, sizeof(command), "python3 -m venv %s", vname);
    int result = system(command);

    if (result == 0) {
        printf("✅ Virtual environment '%s' created successfully!\n", vname);
        printf("👉 To activate it, run:\n\n   source %s/bin/activate\n\n", vname);
    } else {
        printf("❌ Failed to create virtual environment '%s'.\n", vname);
    }

    return 0;
}
