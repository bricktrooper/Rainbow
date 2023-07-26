import os
import shutil

LOG = "https://github.com/bricktrooper/Logs"
CLI = "https://github.com/bricktrooper/CLI"

os.system(f"git clone {LOG} repo/")
os.system(f"pip3 install repo/python --upgrade")
shutil.rmtree("repo/", ignore_errors = True)

os.system(f"git clone {CLI} repo/")
os.system(f"pip3 install repo/ --upgrade")
shutil.rmtree("repo/", ignore_errors = True)

os.system("pip install api/ --upgrade")
shutil.rmtree("api/build", ignore_errors = True)
shutil.rmtree("api/dist", ignore_errors = True)
shutil.rmtree("api/rainbow.egg-info", ignore_errors = True)

if os.path.exists("/usr/local/bin/rainbow"):
    print("/usr/local/bin/rainbow already exists")
    exit(-1)

path = os.getcwd()
os.chdir("/usr/local/bin")
os.system(f"ln -s {path}/rainbow-cli.py rainbow")
