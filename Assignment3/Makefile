GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@g++ main.cpp *.cpp Common/InitShader.o $(OPTIONS) -o part1
	@g++ mainPart2.cpp *.cpp Common/InitShader.o $(OPTIONS) -o part2 
run1: build
	@./part1
run2: build
	@./part2
clean:
	@rm shapes

