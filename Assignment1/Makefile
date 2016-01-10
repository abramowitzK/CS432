GCC_OPTIONS=-Wall -pedantic -I include
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	g++ *.cpp Common/InitShader.o $(OPTIONS) -o red_shapes  
run: build
	@./red_shapes
clean:
	@rm red_shapes

