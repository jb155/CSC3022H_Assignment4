#include "Image.h"

#include <fstream>

namespace BTHJAC013{
	bool loadImageFromFile(std::string fileName){

		//in file stream setup
		ifstream inFilePic;
		//Open file
		inFilePic.open(fileName, ios::in | ios:binary);
		try{
			//check if file can be read
			if(!inFilePic){
				cout << "Can't read image: " << fname << endl;
				exit(1);
			}

			std::string header; 
			int b; //width, height, ------something------

			ifs >> header; 

			if (strcmp(header.c_str(), "P6") != 0) {
				cout << "Can't read input file: " << fname << endl;
				exit(1);
			}

			ifs >> this.width >> this.height >> b; 
			//img.w = w; 
			//img.h = h; 
			//img.pixels = new Image::Rgb[w * h]; // this is throw an exception if bad_alloc
			unsigned char *tempBuffer = new unsigned char[this.width*this.height]();
			ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
			unsigned char pix; // read each pixel one by one and convert bytes to floats 
			for (int i = 0; i < this.width*this.height; ++i) {
				ifs.read(reinterpret_cast<char>(pix), 1); 
				tempBuffer.[i] = pix / 255.f;
			}
			ifs.close(); 

			this.data = move(tempBuffer);

			delete[] tempBuffer;
		} catch (const char *err) { 
			fprintf(stderr, "%s\n", err); 
			ifs.close(); 
		}

		return true;
	}

	void Image(std::string fileName){

	}
}