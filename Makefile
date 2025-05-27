CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

TARGET = snake_game
SRC = main.cpp map/map.cpp include/start_screen.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) -lncursesw

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
