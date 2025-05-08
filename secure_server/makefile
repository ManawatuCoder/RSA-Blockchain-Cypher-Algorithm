# Compiler and target
CC := g++
TARGET := secure_server
EXTENSION := .exe

# Source and object files
SRC := secure_server.cpp ../CryptoManager.cpp
OBJ := $(SRC:.cpp=.o)

# OS detection
ifeq ($(OS),Windows_NT)
    CFLAGS := -c -std=c++11 -Wall -O2 -fconserve-space
    LFLAGS := -lws2_32
    CLEANUP := del /Q
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        EXTENSION := .out
        CFLAGS := -c -std=c++11 -Wall
        LFLAGS :=
        CLEANUP := rm -f
    else ifeq ($(UNAME_S),Linux)
        EXTENSION := .out
        CFLAGS := -c -std=c++11 -Wall
        LFLAGS :=
        CLEANUP := rm -f
    endif
endif

# Targets
all: $(TARGET)$(EXTENSION)

$(TARGET)$(EXTENSION): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(CLEANUP) *.o $(TARGET)$(EXTENSION)
