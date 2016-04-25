Instructions:

	Standard Operation:
		- Use "make" to build the project
		- Use "make run ARGS="<args>" to run the program (args eg. -a i1 i2 out.pgm)
	Test Operation:
		- Ume "make" to Build the project
		- Use "make run-tests" to run pre-defined test cases to test the functionality of the system
	Clean Operation"
		- Use "make clean"  to delete all binary files

Files:

	src/main.cpp: Driver file. Main cllass resides here.
	src/Image.cpp: Image class
	src/Image.h: Header for the image class. Has all the overload functions inside it.
	src/Unittests.cpp: This is where the unit tests are defined.
	src/catch.hpp: This is reposnible for unit Testing.
	build/: Build files and Testing images are found here.
