CXX:=g++
CXXFLAGS:= -c -O3 -Wall -pedantic -Werror -std=c++98 -I ..

SRC_DIR:=source
BIN_DIR:=bin
OBJ_DIR:=obj

CPP_FILES := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/card.cpp \
	$(SRC_DIR)/cardset.cpp \
	$(SRC_DIR)/cardstack.cpp \
	$(SRC_DIR)/operation.cpp \
	$(SRC_DIR)/deck.cpp \
	$(SRC_DIR)/home.cpp 

OBJS_FILES:=${CPP_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o} 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
    
freecell: build_dirs $(OBJS_FILES)
	$(CXX) $(OBJS_FILES) -o $(BIN_DIR)/freecell

all: clean build_dirs freecell

build_dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
    
clean:
	rm -rf $(BIN_DIR)  
	rm -rf $(OBJ_DIR)

.PHONY: clean
