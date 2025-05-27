CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -Imap

TARGET = snake_game

# 모든 cpp 파일을 자동으로 검색
SRC := $(wildcard *.cpp) \
       $(wildcard map/*.cpp) \
       $(wildcard include/*.cpp)

# cpp 파일에 대응되는 o 파일 리스트 생성
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) -lncurses

# 개별 cpp → o 파일 빌드
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
