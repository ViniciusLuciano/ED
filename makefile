OBJS = *.c
CC = gcc
COMPILER_FLAGS = -w -std=c99
LINKER_FLAGS = -lm
OBJ_NAME = siguel

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

get-deps:
	sudo apt-get update;
	sudo apt-get update --fix-missing;
	sudo apt-get install libegl1-mesa-dev;
	sudo apt-get install libgles2-mesa-dev;
	sudo apt-get install libsdl2-dev;
	sudo apt-get install libsdl2-image-dev;
	sudo apt-get install libsdl2-ttf-dev;
	sudo apt-get install libsdl2-mixer-dev;
	sudo apt-get install libssl-dev;	