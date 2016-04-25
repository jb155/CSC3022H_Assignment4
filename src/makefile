CC=g++
CCFLAGS= -std=c++11

SOURCES= main.cpp Image.h Image.cpp
OBJECTS= main.o Image.o

TEST_SOURCES=src/Image.cpp src/Unittests.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

EXE_NAME=imageops

default: $(OBJECTS)
	$(CC) $(SOURCES) -o build/$(EXE_NAME) $(FLAGS)

.cpp.o:
	$(CC) -c $< -o $@ $(FLAGS)

clean:
	rm -f ImageOps *.o

run: default
	cd ./build && ./$(EXE_NAME) $(ARGS)

tests: $(OBJECTS)
	$(CC) $(TEST_SOURCES) -o build/test $(FLAGS)

run-tests: tests
	cd ./build && ./test

