TARGET = operoverloading
#INSTALL_PATH = /usr/local/bin

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

MOVE = mv
MKDIR_P = mkdir -p

CC = g++
CPPFLAGS += -Iinclude -pedantic
CFLAGS += -Wall -std=c++17
LDFLAGS += -Llib
#LDLIBS += -lm 

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(MKDIR_P) $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(MOVE) $(TARGET) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run:
	./$(BIN_DIR)/$(TARGET)

install: $(TARGET)
	cp $(BIN_DIR)/$(TARGET) $(INSTALL_PATH)
	
clean:
	$(RM) $(OBJ) $(BIN_DIR)/$(TARGET)
