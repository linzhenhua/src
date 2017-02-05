.PHONY: clean all
CC = g++
CPPFLAGS = -Wall -g -pthread -std=c++11
BIN = server client
SOURCES = $(BIN.=.cpp)

all: $(BIN)
$(BIN): $(SOURCES) Socket.cpp

clean:
	-rm -rf $(BIN) bin/ obj/ core
