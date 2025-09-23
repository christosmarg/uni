EXEC = menu

SRC_DIR = src
OBJ_DIR = obj
EXEC_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MOVE = mv
MKDIR_P = mkdir -p

CC = gcc
CPPFLAGS += -Iinclude
CFLAGS += -Wall
LDFLAGS += -Llib
LDLIBS += -lm -lncurses

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(MKDIR_P) $(EXEC_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(MOVE) $(EXEC) $(EXEC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run:
	./$(EXEC_DIR)/$(EXEC)

clean:
	$(RM) $(OBJ) $(EXEC_DIR)/$(EXEC)