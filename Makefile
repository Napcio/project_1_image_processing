CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20
SRC = src/Milestone1.cpp src/main.cpp src/TgaContainer.cpp src/Pixel.cpp src/Method.cpp
OUT = project1.out

.PHONY: all tasks

all : project1.out

project1.out :
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

tasks :
	./project1.out ./output/part11.tga ./input/circles.tga multiply ./input/layer1.tga
	./project1.out ./output/part12.tga ./input/layer1.tga flip
	./project1.out ./output/part13.tga ./input/layer1.tga subtract ./input/layer2.tga