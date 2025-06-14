CXX := g++
CXXFLAGS := -Wall -std=c++17

# .git, .vscode, 숨김 디렉토리 제외
SUBDIRS := $(shell find . -type d \
            ! -path "./.*" \
            ! -path "./.git*" \
            ! -path "./.vscode*" \
            ! -path "./build*")

SRC := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.cpp))
OBJ := $(SRC:.cpp=.o)
INCLUDES := $(addprefix -I, $(SUBDIRS))

TARGET := snake_game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(INCLUDES) -lncursesw

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDES)

clean:
	rm -f $(OBJ) $(TARGET)

