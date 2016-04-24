/*                                /   \       
 _                        )      ((   ))     (
(@)                      /|\      ))_((     /|\
|-|                     / | \    (/\|/\)   / | \                      (@)
| | -------------------/--|-voV---\`|'/--Vov-|--\---------------------|-|
|-|  Image.cpp              '^`   (o o)  '^`              04-04-2016  | |
| |								  `\Y/'								  |-|
|-|																	  | |
| |						Created by: Jacques Botha					  |-|
|-|																	  | |
| |			Project: CSC3022H Assignment4: Image processing			  |-|
|_|___________________________________________________________________| |
(@)              l   /\ /         ( (       \ /\   l                `\|-|
                 l /   V           \ \       V   \ l                  (@)
                 l/                _) )_          \I
                                   `\ /'
									 *		"There be dragons son" - Wise man
*/

#include <fstream>
#include <sstream> 

#include "Image.h"

namespace BTHJAC013{
	//Basic constructor
	Image::Image(){
		this->name = "";
		this->width = 0;
		this->height = 0;
	}

	bool Image::loadImage(std::string fileName){
		this->name = fileName;
		//in file stream setup
		std::ifstream inFilePic;
		try{
			//Open file
			inFilePic.open(fileName, std::ios::in | std::ios::binary);
			//check if file can be read
			if(!inFilePic.is_open()){
				std::cout << "Can't read image: " << fileName << std::endl;
				return false;
			}

			std::string lineRead; 

			while (!inFilePic.eof()){
				getline(inFilePic, lineRead);

				if(lineRead[0]=='#' || lineRead == "P5"){
					continue;
				} else if (lineRead == "255"){											//end of image
					break;
				} else {
					std::stringstream stringS(lineRead);
					std::string temp;

					getline(stringS, temp, ' ');
					this->width = std::stoi(temp);										//set width of the image

					getline(stringS, temp, ' ');
					this->height = std::stoi(temp);										//set height of the image
				}
			}

			unsigned char * imageBuf = new unsigned char [this->width*this->height];
			inFilePic.read((char*)imageBuf, this->width*this->height);
			inFilePic.close();

			//this->data = move(imageBuf);
			//delete[] imageBuf;

			this->data = std::unique_ptr<unsigned char []>(imageBuf);

			return true;
		}catch (...){
			return false;
		}
}
	bool Image::saveImage (std::string fileName){
		return true;
	}
}