GCC_OPTIONS=-I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)

build: 
	@$(MAKE) --directory Assignment9P1 build
	@$(MAKE) --directory Assignment9P2 build
run1: build
	@$(MAKE) --directory Assignment9P1 run
run2: build
	@$(MAKE) --directory Assignment9P2 run

clean:
	@$(MAKE) --directory Assignment9P1 clean
	@$(MAKE) --directory Assignment9P2 clean
