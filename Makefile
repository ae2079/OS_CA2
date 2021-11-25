CC = g++
BUILD_DIR = build
SRC_DIR = src
# MAIN_MAP = map
# MAIN_REDUCE = reduce
#INCLUDE_DIR = includes
CFLAGS = -std=c++17 #-I$(INCLUDE_DIR)

MAIN_EXECUTABLE_FILE = main.out
REDUCE_EXECUTABLE_FILE = reduce.out
MAP_EXECUTABLE_FILE = map.out


MAIN_OBJECTS = $(BUILD_DIR)/Main.o

REDUCE_OBJECTS = $(BUILD_DIR)/Reduce.o

MAP_OBJECTS = $(BUILD_DIR)/Map.o 

MainSensitivityList = $(SRC_DIR)/Main.cpp

MapSensitivityList = $(SRC_DIR)/Map.cpp

ReducetSensitivityList = $(SRC_DIR)/Reduce.cpp 

all: $(BUILD_DIR) $(MAIN_EXECUTABLE_FILE) $(REDUCE_EXECUTABLE_FILE) $(MAP_EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(MAIN_EXECUTABLE_FILE): $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) $(MAIN_OBJECTS) -o $(MAIN_EXECUTABLE_FILE)

$(BUILD_DIR)/Map.o: $(MapSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Map.cpp -o $(BUILD_DIR)/Map.o

$(MAP_EXECUTABLE_FILE): $(MAP_OBJECTS)
	$(CC) $(CFLAGS) $(MAP_OBJECTS) -o $(MAP_EXECUTABLE_FILE)

$(BUILD_DIR)/Reduce.o: $(ReducetSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Reduce.cpp -o $(BUILD_DIR)/Reduce.o

$(REDUCE_EXECUTABLE_FILE): $(REDUCE_OBJECTS)
	$(CC) $(CFLAGS) $(REDUCE_OBJECTS) -o $(REDUCE_EXECUTABLE_FILE)

.PHONY: clean
# clean:
# 	rm -rf $(BUILD_DIR) *.o *.out \
# 	rmdir -rf systems \
# 	rmdir -rf pipes/*
clean:
	rm -rf $(BUILD_DIR) *.o *.out