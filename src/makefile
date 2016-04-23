CC=g++
CCFLAGS= -std=c++11

SOURCES= main.cpp Image.h Image.cpp
OBJECTS= main.o Image.o

Imageops: $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o ImageOps $(LIBS)

.cpp.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f ImageOps *.o

