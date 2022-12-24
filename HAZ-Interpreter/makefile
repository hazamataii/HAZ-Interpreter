CC = gcc
CFLAGS = -g -mtune=native -march=native -pipe#remove or comment out -pipe if compiling on a low memory system
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
#LINUX_LDFLAGS = ""
WIN32_LDFLAGS = -municode #-lshell32 -lgdi32
#-limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid#-mwindows
#
OUTPUT = ../build/BIN/HAZ_Interpreter.exe

all:$(OUTPUT)

$(OUTPUT): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(WIN32_LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@




clean:
	rm -r $(OBJ)
	rm $(OUTPUT)