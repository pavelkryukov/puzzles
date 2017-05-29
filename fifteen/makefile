CXX:=g++
CXXFLAGS:= -c -O3 -Wall -pedantic -Werror -std=c++98 -I ..

SRC_DIR:=source
BIN_DIR:=bin
OBJ_DIR:=obj

CPP_FILES := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/operation.cpp \
	$(SRC_DIR)/fifteen.cpp

OBJS_FILES:=${CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o} 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
    
fifteen: build_dirs $(OBJS_FILES)
	$(CXX) $(OBJS_FILES) -o $(BIN_DIR)/fifteen

all: clean build_dirs fifteen

build_dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
    
clean:
	rm -rf $(BIN_DIR)  
	rm -rf $(OBJ_DIR)

.PHONY: clean
