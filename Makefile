# "Inspiration" taken from: https://gitlab.fit.cvut.cz/husekrad/pa2-cvika-2022/tree/master/cv10/semestralka

LOGIN = horanvoj
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -g -Wall -pedantic
FLAGS =  $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf -DRESOURCES_PATH=\"src/resources/\"

ZIP = Makefile Doxyfile DOCUMENTATION.md zadani.txt prohlaseni.txt \
  .gitignore $(wildcard examples/*) $(wildcard src/*)

SOURCES = $(wildcard src/*.cpp src/entity/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

.PHONY: all compile run valgrind doc clean count zip

all: compile doc

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@

run: compile
	./${LOGIN}

valgrind: compile
	valgrind ./${LOGIN}

doc: doc/index.html

doc/index.html: DOCUMENTATION.md Doxyfile $(wildcard src/* src/entity/*)
	doxygen Doxyfile

count:
	wc -l src/*.h src/*.cpp src/entity/*.h src/entity/*.cpp src/resources/strings/*.h

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip

zip: ${LOGIN}.zip

${LOGIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${LOGIN}/
	cp --parents -r $^ tmp/${LOGIN}/
	cd tmp/ && zip -r ../$@ ${LOGIN}/
	rm -rf tmp/

build/%.dep: src/%.cpp src/*
	@mkdir -p build/
	@mkdir -p build/entity
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

include ${DEPS}

