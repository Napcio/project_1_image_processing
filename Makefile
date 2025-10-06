CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20
SRC = src/Milestone1.cpp src/main.cpp src/TgaContainer.cpp src/Pixel.cpp src/Method.cpp src/KernelOperations.cpp
OUT = ./project1.out

.PHONY: all tasks extra collage

all : $(OUT)

$(OUT) : $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

tasks : $(OUT)
	$(OUT) ./output/part11.tga ./input/circles.tga multiply ./input/layer1.tga
	$(OUT) ./output/part12.tga ./input/layer1.tga flip
	$(OUT) ./output/part13.tga ./input/layer1.tga subtract ./input/layer2.tga

extra : $(OUT)
	$(OUT) ./output/inverted_car.tga ./input/car.tga invert
	$(OUT) ./output/grayscale_car.tga ./input/car.tga grayscale
	$(OUT) ./output/sepia_car.tga ./input/car.tga sepia
	$(OUT) ./output/sharpened_car.tga ./input/car.tga sharpen 1
	$(OUT) ./output/blurred_car.tga ./input/car.tga blur


collage : $(OUT)
	$(OUT) ./output/collage_test.tga ./input/car.tga ./input/circles.tga ./input/layer1.tga ./input/pattern2.tga mosaic 2 2