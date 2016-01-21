GCC_OPTIONS=-pedantic -I include -std=c++11
GL_OPTIONS=-lGLEW -lGL -lglut
OPTIONS=$(GCC_OPTIONS) $(GL_OPTIONS)


build: 
	@$(MAKE) --directory part1 build
	@$(MAKE) --directory part2 build
run1: build
	@$(MAKE) --directory part1 run1
run2: build
	@$(MAKE) --directory part2 run2
clean:
	@$(MAKE) --directory part1 clean
	@$(MAKE) --directory part2 clean

