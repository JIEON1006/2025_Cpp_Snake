# 컴파일러 및 옵션
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -lncurses

# 파일 정의
TARGET = snake_game
SRC = main.cpp map/map.cpp
OBJ = $(SRC:.cpp=.o)

# 기본 규칙
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# 정리
clean:
	rm -f $(OBJ) $(TARGET)
