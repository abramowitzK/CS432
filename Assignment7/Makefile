GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@g++ *.cpp Common/InitShader.o $(OPTIONS) -o assignment7
run: build
	@./assignment7
clean:
	@rm assignment7

