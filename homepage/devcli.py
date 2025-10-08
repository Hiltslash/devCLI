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

cc = os.path.expanduser("~/Codingprojects")  # canonical path to your projects
# top-level project-type directories (e.g. python, web, lua)
try:
    dirs = [d for d in os.listdir(cc) if os.path.isdir(os.path.join(cc, d))]
except Exception:
    dirs = []
fils = None

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
# browse prompts will be created dynamically inside the menu loop so choices reflect
# current filesystem state (and we can limit to latest 15 modified folders)
nptype = None
message = None
version = 1.1

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
            elif ans["hm"] == "Navigate Projects":
                loc = 4
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

        elif loc == 4:
            # Refresh project-type directories
            try:
                dirs = [d for d in os.listdir(cc) if os.path.isdir(os.path.join(cc, d))]
            except Exception:
                dirs = []

            if not dirs:
                message = f"No project-type directories found in {cc}"
                loc = 0
                continue

            # Prompt user to pick a project-type folder
            browseprojecttype = inquirer.List(
                "bpt",
                message="Select a directory",
                choices=dirs
            )
            ans = inquirer.prompt([browseprojecttype])
            if ans is None:
                loc = 0
                continue

            browseprojecttypeANSWER = ans["bpt"]
            project_dir = os.path.join(cc, browseprojecttypeANSWER)

            # Gather subfolders and sort by modified time (descending), keep only 15 latest
            try:
                entries = [
                    d for d in os.listdir(project_dir)
                    if os.path.isdir(os.path.join(project_dir, d))
                ]
            except Exception:
                message = f"Unable to list projects in {project_dir}"
                loc = 0
                continue

            def mtime(path):
                try:
                    return os.path.getmtime(path)
                except Exception:
                    return 0

            entries_with_mtime = [(e, mtime(os.path.join(project_dir, e))) for e in entries]
            entries_with_mtime.sort(key=lambda x: x[1], reverse=True)
            latest_entries = [e for e, _ in entries_with_mtime][:15]

            if not latest_entries:
                message = f"No projects found inside {project_dir}"
                loc = 0
                continue

            browseprojectselection = inquirer.List(
                "bps",
                message=f"Select a project (showing {len(latest_entries)} most recently modified)",
                choices=latest_entries
            )
            ans = inquirer.prompt([browseprojectselection])
            if ans is None:
                loc = 0
                continue

            browseprojectselectionANSWER = ans["bps"]
            subprocess.run(["code", os.path.join(project_dir, browseprojectselectionANSWER)])

except KeyboardInterrupt:
    sys.stdout.write("\033[?25h")
    sys.stdout.flush()
    clear()
    exit(0)
