OBJS = *.c
CC = gcc
COMPILER_FLAGS = -w -std=c99
LINKER_FLAGS = -lm
OBJ_NAME = siguel

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

	