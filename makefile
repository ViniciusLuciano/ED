OBJS = *.c
CC = gcc
COMPILER_FLAGS = -g -std=c99 -fstack-protector-all
LINKER_FLAGS = -lm
OBJ_NAME = siguel

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

	
