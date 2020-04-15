TARGET = minecurses

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CPPFLAGS += -Iinclude
CFLAGS += -Wall 
LDFLAGS += -Llib
LDLIBS += -lm -lncurses -lSDL2 -lSDL2_mixer -pthread

MOVE = mv
MKDIR_P = mkdir -p

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
