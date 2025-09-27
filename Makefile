CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20
SRC = src/main.cpp src/TgaContainer.cpp src/Pixel.cpp
OUT = project1.out

all : project1.out

project1.out :
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)