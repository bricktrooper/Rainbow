import os
import shutil

LOG = "https://github.com/bricktrooper/Logs"
CLI = "https://github.com/bricktrooper/CLI"

TEMP = "temp"

shutil.rmtree(TEMP, ignore_errors = True)

os.mkdir(TEMP)
os.chdir(TEMP)

os.system(f"git clone {LOG} Logs")
os.chdir("Logs/python/")
os.system("pip3 install .")
os.chdir("../../")

os.system(f"git clone {CLI} CLI")
os.chdir("CLI/")
os.system("pip3 install .")
os.chdir("../../")

shutil.rmtree(TEMP)

os.chdir("api")
os.system("pip install .")
os.chdir("..")

if os.path.exists("/usr/local/bin/rainbow"):
    print("/usr/local/bin/rainbow already exists")
    exit()

path = os.getcwd()
os.chdir("/usr/local/bin")
os.system(f"ln -s {path}/rainbow-cli.py rainbow")
