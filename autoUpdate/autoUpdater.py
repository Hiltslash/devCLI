import requests


def updateFile(user: str, repo: str, branch: str = "main", filepath: str = "README.md", filetarget = None):
    url = f"https://raw.githubusercontent.com/{user}/{repo}/{branch}/{filepath}"
    response = requests.get(url)
    print(url)
    if response.status_code == 200:
        with open("file.txt", "wb") as f:
            f.write(response.content)
        print("File downloaded!")
    else:
        print("Failed to download:", response.status_code)
    if filetarget:
        with open(filetarget, "wb") as f:
            f.write(response.content)
    else:
        with open(filepath, "wb") as f:
            f.write(response.content)
