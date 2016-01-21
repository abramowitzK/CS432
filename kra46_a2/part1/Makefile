GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@g++ *.cpp Common/InitShader.o $(OPTIONS) -o part1
run1: build
	@./part1
clean:
	@rm part1

