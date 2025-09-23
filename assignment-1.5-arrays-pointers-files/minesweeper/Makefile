TARGET = minesweeper

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CPPFLAGS += -Iinclude
CFLAGS += -Wall 
LDFLAGS += -Llib

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif
ifeq ($(OS),Linux)
    detected_OS := Linux
else
    detected_OS := $(shell uname)
endif

ifeq ($(detected_OS),Linux)
	LDLIBS += -lm -lncurses 
	MOVE = mv
	MKDIR_P = mkdir -p
endif
ifeq ($(detected_OS),Windows)
	LDLIBS += -lm -LC:\PDCurses\wincon -lpdcurses
	MOVE = move
	MKDIR_P = md
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(MKDIR_P) $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(MOVE) $(TARGET) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run:
	./$(BIN_DIR)/$(TARGET)

clean:
	$(RM) $(OBJ) $(BIN_DIR)/$(TARGET)