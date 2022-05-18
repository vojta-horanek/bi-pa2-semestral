# Source for base file: https://gitlab.fit.cvut.cz/husekrad/pa2-cvika-2022/tree/master/cv10/semestralka

LOGIN = horanvoj
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -g -Wall -pedantic
FLAGS =  $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf -DRESOURCES_PATH=\"assets/\"

ZIP = Makefile Doxyfile DOCUMENTATION.md zadani.txt prohlaseni.txt \
  .gitignore $(wildcard examples/*) $(wildcard src/*) $(wildcard assets/*)

SOURCES = $(wildcard src/*.cpp src/entity/*.cpp src/menu/*.cpp src/parser/*.cpp src/render/*.cpp src/utils/*.cpp src/test/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

.PHONY: all compile run doc clean

all: compile doc

test: FLAGS += -DTEST
test: compile run

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -c $< -o $@

run: compile
	./${LOGIN}

doc: doc/index.html

doc/index.html: DOCUMENTATION.md Doxyfile $(wildcard src/* src/entity/* src/menu/*.cpp src/parser/*.cpp src/render/*.cpp src/utils/*.cpp src/test/*.cpp)
	doxygen Doxyfile

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip

build/%.dep: src/%.cpp src/*
	@mkdir -p build/ build/entity build/menu build/render build/parser build/utils build/test
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

include ${DEPS}

