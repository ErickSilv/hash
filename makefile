#Makefile

#Compiler
CXX = g++

#Flags
COMPILE_FLAG = -std=c++11

#Path
SRC_PATH = ./src/driver_hashtable.cpp
INCLUDE_PATH = ./include/hashtable.h ./include/hashtable.cpp

#Executable
BIN_NAME = ./bin/hashtbl

list: $(SRC_PATH) $(INCLUDE_PATH)
	$(CXX) $(COMPILE_FLAG) $(SRC_PATH) $(INCLUDE_PATH) -o $(BIN_NAME)