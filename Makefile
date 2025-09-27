all : project1.out

project1.out :
	g++ -Wall -Wextra -Werror -std=c++20 -o project1.out src/main.cpp src/TgaContainer.cpp src/Pixel.cpp