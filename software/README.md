# Software

Python scripts for communicating with the Rainbow boards over a serial connection.
This software provides a `rainbow` module that can be used in Python scripts.

#### Quick Installation

Run the following script to install the `rainbow` command to `/usr/local/bin`
```
python3 install.py
```

This will install the `log`, `cli`, and `rainbow` Python modules as well.

#### Manual Installation

The software requires the `log` and `cli` modules found on GitHub:
```
https://github.com/bricktrooper/Logs/tree/master/python
https://github.com/bricktrooper/CLI
```
Clone these repositories and follow the instructions to install the modules using `pip`.

Finally, install the `rainbow` module from this repository:
```
cd api
pip install .
```

Then to run the CLI tool, use the following command:
```
python3 rainbow-cli.py
```

You can symlink this script if needed.
