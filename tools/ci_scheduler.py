import subprocess

PATHS = (
    ("bindings", "docs", "samd", "esp32s2", "raspberrypi"),
    ((".md", ".rst"), "docs")
)

files = subprocess.check_output("git diff --name-only origin/dynamic-ci", shell=True).strip().decode("utf-8", "strict").replace("\n","")
for x in range(len(PATHS)):
    if type(PATHS[x][0]) is tuple:
        for y in range(len(PATHS[x][0])):
            if (files.find(PATHS[x][0][y]) >= 0):
                print(PATHS[x][0][y])
    else:
        if (files.find(PATHS[x][0]) >= 0):
            print(PATHS[x][0])
