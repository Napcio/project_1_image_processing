all : imageProcessor

imageProcessor :
	g++ -Wall -Wextra -Werror -std=c++20 -o out src/main.cpp src/TgaContainer.cpp src/Pixel.cpp