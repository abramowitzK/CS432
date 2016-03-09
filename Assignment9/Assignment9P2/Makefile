GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@g++ *.cpp Common/InitShader.o $(OPTIONS) -o assignment9
run: build
	@./assignment9
clean:
	@rm assignment9

