from distutils.core import setup

setup(
	name = "rainbow",
	version = "0.1.1",
	description = "API for interacting with the Rainbow RGB controller board.",
	author = "Kyle Pinto",
	author_email = "kylepinto1018@gmail.com",
	url = "https://github.com/bricktrooper/Rainbow",
	packages = ["rainbow"],
	dependencies = ["log", "cli", "pyserial"]
)
