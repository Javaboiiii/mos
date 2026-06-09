CXX = g++
CXXFLAGS = -std=c++23 -Iinclude -Wall -Wextra

SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data
OUT_DIR = output

TARGET = $(OUT_DIR)/main

SRCS = \
	$(SRC_DIR)/phase2.cpp \
	$(SRC_DIR)/Memory.cpp \
	$(SRC_DIR)/MMU.cpp \
	$(SRC_DIR)/CPU.cpp \
	$(SRC_DIR)/OS.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	$(TARGET) < $(DATA_DIR)/input.txt

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all run clean
