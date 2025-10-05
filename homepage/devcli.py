#!/usr/bin/env python3.13

import os
import sys
import subprocess
from datetime import datetime
import inquirer

# Hide terminal cursor
sys.stdout.write("\033[?25l")
sys.stdout.flush()

# Clear function
def clear():
    os.system('clear')

# Determine path to Resources folder inside the app bundle
if getattr(sys, 'frozen', False):
    # Running inside py2app bundle
    BASE_PATH = os.path.abspath(os.path.join(os.path.dirname(sys.executable), '..', 'Resources'))
else:
    # Running as a normal script
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))

# Inquirer menus
homemenu = inquirer.List(
    "hm",
    message="Select an option",
    choices=["New Project", "Backup Codingprojects", "Navigate Projects", "Quit"]
)
newproject = inquirer.List(
    "np",
    message="Select an option",
    choices=["Python", "Web (Flask)", "Web (Vanilla)", "Love2D", "C", "Back"]
)
newprojectname = inquirer.Text(
    "npn",
    message="Enter name for new project",
)

nptype = None
message = None
version = 1.0

try:
    clear()
    loc = 0
    while True:
        clear()
        formattedTime = datetime.now().strftime("%H:%M")
        print(f"DEVCLI | v{version} | {formattedTime}")
        if not loc:
            if message:
                print(message)
            ans = inquirer.prompt([homemenu])
            if ans["hm"] == "New Project":
                loc = 1
            elif ans["hm"] == "Backup Codingprojects":
                loc = 3
            elif ans["hm"] == "Quit":
                sys.stdout.write("\033[?25h")
                sys.stdout.flush()
                clear()
                exit(0)
            message = None

        elif loc == 1:
            ans = inquirer.prompt([newproject])
            if ans["np"] == "Back":
                loc = 0
            else:
                loc = 2
                nptype = ans["np"]

        elif loc == 2:
            ans = inquirer.prompt([newprojectname])
            name = ans["npn"]

            # Path to the executable inside Resources
            exe_path = os.path.join(BASE_PATH, nptype)
            codingprojects_dir = os.path.expanduser("~/Codingprojects")

            # Map project types to folder names
            project_type_map = {
                "Python": "python",
                "Web (Flask)": "python",
                "Web (Vanilla)": "web",
                "Love2D": "lua",
                "C": "c"
            }
            project_type_dir = os.path.join(codingprojects_dir, project_type_map.get(nptype, "misc"))

            # Run the executable with the new project name as argument
            subprocess.run([exe_path, name], cwd=project_type_dir)

            # Open in VS Code
            subprocess.run(["code", f"./{name}"], cwd=project_type_dir)

            loc = 0
            message = "Complete!"

        elif loc == 3:
            # Run backup script
            subprocess.run(["/bin/bash", "/Users/beaudavidson/autocommit.sh"])
            input("...Press Enter to continue...")
            loc = 0
            clear()

except KeyboardInterrupt:
    sys.stdout.write("\033[?25h")
    sys.stdout.flush()
    clear()
    exit(0)
