CXX:=g++
CXXFLAGS:= -c -O3 -Wall -Werror -pedantic -std=c++98

SRC_DIR:=source
BIN_DIR:=bin
OBJ_DIR:=obj

CPP_FILES := \
	$(SRC_DIR)/cell.cpp      \
	$(SRC_DIR)/blocklist.cpp \
	$(SRC_DIR)/sudoku.cpp    \
	$(SRC_DIR)/main.cpp 

OBJS_FILES:=${CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o} 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
    
sudoku: build_dirs $(OBJS_FILES)
	$(CXX) $(OBJS_FILES) -o $(BIN_DIR)/sudoku

all: build_dirs sudoku

build_dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
    
clean:
	rm -rf $(BIN_DIR)  
	rm -rf $(OBJ_DIR)

.PHONY: clean
