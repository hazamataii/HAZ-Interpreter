CC = gcc
CFLAGS = -g
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
#NOTE remove all of the flags or comment them out in Linux build
LDFLAGS = -municode -lshell32 -lgdi32
#-limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid#-mwindows#-lglfw3dll
OUTPUT = build/BIN/HAZ_Interpreter.exe

all:$(OUTPUT)

$(OUTPUT): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@




clean:
	rm -r $(OBJ)
	rm $(OUTPUT)