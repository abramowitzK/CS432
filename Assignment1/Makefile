GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	g++ *.cpp *.h Common/InitShader.o $(OPTIONS) -o red_shapes 
run: build
	@./red_shapes
clean:
	@rm red_shapes

