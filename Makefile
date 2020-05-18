COMPILER = g++
COMPILEFLAGS = -std=c++14 -Wall -pedantic
VALGRINDFLAFS = --leak-check=full
LINKLIBRARY = -lncurses
FILES := $(wildcard src/*.cpp)

%.o: %.cpp
	@echo "Building " $@
	@$(COMPILER) $(COMPILEFLAGS) -c -o $@ -c $< $(LINKLIBRARY)
	@$(COMPILER) $(COMPILEFLAGS) -MM -MT $*.o $*.cpp $(LINKLIBRARY) > $*.d

compile: $(FILES:.cpp=.o)
	@echo "Compiling..."
	@$(COMPILER) $(COMPILEFLAGS) $(FILES:.cpp=.o) -o rpg $(LINKLIBRARY)
	@echo "Compiled."

memcheck: clean compile
	@echo "Compiling, running valgrind.."
	@$(COMPILER) $(COMPILEFLAGS) -g $(FILES:.cpp=.o) -o rpg $(LINKLIBRARY)
	valgrind ./rpg $(VALGRINDFLAGS)

clean:
	@echo "Cleaning generated files.."
	@rm -f -- src/*.o
	@rm -f -- src/*.d
	@rm -rf -- rpg
	@echo "Cleaning done."

all: clean compile

help:
	@echo "These are valid commands and their description"
	@echo "	make all - runs make clean doc compile run"
	@echo "	make compile - compile the source files"
	@echo "	make run - runs the executable"
	@echo "	make clean - deletes generated files"
	@echo "	make memcheck - compiles with -g and runs in valgrind"
