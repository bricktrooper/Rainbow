# compiler / linker
CC = xc8-cc

# compiler / linker flags
FLAGS += -mcpu=16f15325
FLAGS += -mc90lib
FLAGS += -mwarn=0

# linker libraries
LIBS +=

# source file directories
# NOTE: include paths are searched in this order
DIR += peripherals
DIR += drivers
DIR += utilities

# artifacts folder
ART = artifacts

# hex binary name
BIN = rainbow
