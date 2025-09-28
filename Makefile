.PHONY: all tasks

all : project1.out

project1.out :
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

tasks : project1.out
	./project1.out ./output/part11.tga ./input/circles.tga multiply layer1.tga
	./project1.out ./output/part12.tga ./input/layer1.tga flip
	./project1.out ./output/part13.tga ./input/layer1.tga subtract ./input/layer2.tga