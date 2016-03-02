GCC_OPTIONS=-I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@g++ *.cpp Common/InitShader.o $(OPTIONS) -o assignment8
run: build
	@./assignment8
clean:
	@rm assignment8

