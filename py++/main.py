#! /usr/bin/env python3.12
import sys
import subprocess

newlines = []

try:
    file = sys.argv[1]
except IndexError:
    print("Please provide a file to run.")
    exit()

# Read the file and replace `++` and `--`
with open(file, "r") as f:
    scriptlines = f.readlines()

for line in scriptlines:
    # Replace '++' with '+=' and '--' with '-='
    if "++" in line or "--" in line:
        nline = line.replace("++", "+= 1").replace("--", "-= 1")
        newlines.append(nline)
    else:
        newlines.append(line)

# Write the modified lines to 'running.py'
with open("running.py", "w") as f:
    f.writelines(newlines)

# Run the new script with subprocess
try:
    result = subprocess.run(['python3.12', 'running.py'], check=True, capture_output=True, text=True)
    print(result.stdout)
    print(result.stderr)
except subprocess.CalledProcessError as e:
    print(f"Error running script: {e}")
    print(f"stderr: {e.stderr}")

# Remove the 'running.py' file after execution
subprocess.run(["rm", "running.py"], check=True)
