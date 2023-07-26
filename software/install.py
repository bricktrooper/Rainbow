import os
import shutil

LOG = "https://github.com/bricktrooper/Logs"
CLI = "https://github.com/bricktrooper/CLI"

TEMP = "temp"

shutil.rmtree(TEMP, ignore_errors = True)

os.mkdir(TEMP)

os.system(f"git clone {LOG} {TEMP}/Logs")
os.system(f"pip3 install {TEMP}/Logs/python")

os.system(f"git clone {CLI} {TEMP}/CLI")
os.system(f"pip3 install {TEMP}/CLI")

shutil.rmtree(TEMP)

os.system("pip install api")

if os.path.exists("/usr/local/bin/rainbow"):
    print("/usr/local/bin/rainbow already exists")
    exit()

path = os.getcwd()
os.chdir("/usr/local/bin")
os.system(f"ln -s {path}/rainbow-cli.py rainbow")
