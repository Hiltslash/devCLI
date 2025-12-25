#!/usr/bin/env python3

import os
import sys
import subprocess

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


nptype = None
message = None
version = "1.3"

try:
    clear()
    while True:
        clear()
        nptype = sys.argv[2]
        name = sys.argv[1]
            # Path to te executable inside Resources
        exe_path = os.path.join(BASE_PATH, nptype)
        codingprojects_dir = os.path.expanduser("~/Codingprojects")
        clear()
        i_cant_think_of_a_variable_name = bool(sys.argv[3])
        if i_cant_think_of_a_variable_name:
            gitRepo = True
            project_type_dir = os.path.join(codingprojects_dir, "github")
        else:
            gitRepo = False
        # Map project types to folder names
            project_type_map = {
                "Python": "python",
                "Web (Flask)": "python",
                "Web (Vanilla)": "web",
                "Love2D": "lua",
                "C": "c",
                "Go": "go"
            }
            project_type_dir = os.path.join(codingprojects_dir, project_type_map.get(nptype, "misc"))

        # Run the executable with the new project name as argument
        subprocess.run([exe_path, name], cwd=project_type_dir)

        if gitRepo:
            gcwd =os.path.join(project_type_dir, name)
            subprocess.run(["git", "init"], cwd=gcwd)
            subprocess.run(["git", "branch", "-m", "main"], cwd=gcwd)
            subprocess.run(["touch", "readme.md"], cwd=gcwd) 
            subprocess.run(["git", "add", "."], cwd=gcwd)               
            subprocess.run(["git", "commit", "-m", "Initial Commit"], cwd=gcwd)
            input()
            print("Project Setup. Link your repository to github at github.com")

        # Open in VS Code
        subprocess.run(["code", f"./{name}"], cwd=project_type_dir)



except KeyboardInterrupt:
    sys.stdout.write("\033[?25h")
    sys.stdout.flush()
    clear()
    exit(0)
