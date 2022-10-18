CC = gcc
#WINDOWS FLAGS
FLAGS = -municode -lglew32 -lopengl32 #-mwindows -luser32
#LINUX FLAGS
#FLAGS = -lglew32 -lopengl32
#WINDOWS SRC
SRC = ./src/main.c ./src/win/win.c ./src/win/cmd.c ./src/win/file/file.c ./src/tokens/token.c
#LINUX SRC
#SRC = ./src/main.c ./src/linux/linux.c ./src/win/file/file.c ./src/tokens/token.c

all:
	$(CC) -std=c99 -o "./build/BIN/HAZ_Interpreter.exe" $(SRC) $(FLAGS)