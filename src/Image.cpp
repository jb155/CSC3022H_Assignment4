#include "Image.h"

#include <fstream>

namespace BTHJAC013{
	bool loadImage(std::string fileName){
		this->name = fileName;
		//in file stream setup
		std::ifstream inFilePic;
		try{
			//Open file
			//check if file can be read
			if(!inFilePic.open(fileName, std::ios::in | std::ios:binary);){
				cout << "Can't read image: " << fname << endl;
				return false;
			}

			std::string lineRead; 

			while (!inFile.eof()){
				getline(inFile, lineRead);

				if(lineRead[0]=='#' || line == "P5"){
					continue;
				} else if (lineRead == "255"){											//end of image
					break;
				} else {
					std::stringstream strinS(lineRead);
					std::string temp;

					getline(strinS, temp, ' ');
					this->width = std::stoi(temp);										//set width of the image

					getline(strinS, temp, ' ');
					this->height = std::stoi(temp);										//set height of the image
				}
			}

			unsigned char * imageBuf = new unsigned char [this->width*this->height];
			inFile.read((char*)imageBuf, this->width*this->height);
			infile.close();

			this->data = move(imageBuf);
			delete[] imageBuf;

			//this->data = std::unique_ptr<unsigned char []>(imageBuf);

		return true;
	}catch (Exception e){
		return false;
	}

	//Basic constructor
	void Image(){
		this.name = "";
		this.width = 0;
		this.height = 0;
	}
}