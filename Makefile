# Custom project include
PROJECT_INCLUDE_DIR = include

# Compiler settings
CXX = g++
CXXFLAGS = -w -Wextra -std=c++17 \
           -I$(PROJECT_INCLUDE_DIR) \
           -I$(PROJECT_INCLUDE_DIR)/lib \
           -Isrc/lib \
           -Iinclude \
           -Isrc


# Linker flags
LIBS = -lraylib -L/opt/homebrew/lib

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/game

# Source and Object Files
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIRS = $(sort $(dir $(OBJS)))

# Targets
all: directories $(TARGET)

directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	mkdir -p $(OBJ_DIRS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	LD_LIBRARY_PATH=/usr/local/lib $(TARGET)
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

rebuild: clean all

.PHONY: all clean rebuild run directories

# Move headers from src to include (manual maintenance)
move-headers:
	find src -name "*.hpp" -exec bash -c ' \
		for file; do \
			dest="include/$$(dirname "$${file#src/}")"; \
			mkdir -p "$$dest"; \
			mv "$$file" "$$dest"; \
		done' bash {} +

raylib:
	./install_raylib.sh