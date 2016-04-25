/*                                /   \       
 _                        )      ((   ))     (
(@)                      /|\      ))_((     /|\
|-|                     / | \    (/\|/\)   / | \                      (@)
| | -------------------/--|-voV---\`|'/--Vov-|--\---------------------|-|
|-|  Image.h                '^`   (o o)  '^`              04-04-2016  | |
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


#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include <iostream>

namespace BTHJAC013 {
	class Image
	{
		private:
			std::string name; 														//Name of the image bieng processed
			int width, height;														//Pixel dimensions of the image bieng read
			std::unique_ptr<unsigned char[]> data;									//Data of the buffered image
		public:
			Image();
			Image(std::string fileName){
				if(!loadImage(fileName)){
					std::cout<<"Could not successfully load in image " + fileName << std::endl;
				}
			}
			~Image(){
				delete[] &data;
			}

			bool loadImage(std::string file);										//load the image file in. Save/parse to the data var
			bool saveImage(std::string file);										//save the image data to given file name

			std::string getName(void){return name;}

			// Copy Constructor														//Was told it's good practice to do this, even if it wont be used
			Image(const Image &rhs) {
				this->name = rhs.name;
				this->width = rhs.width;
				this->height = rhs.height;
				this->loadImage(this->name);
			}

			// Move Constructor														//Was told it's good practice to do this, even if it wont be used
			Image(Image &&rhs) {
				this->name = std::move(rhs.name);
				this->width = rhs.width;
				this->height = rhs.height;
				this->data = std::move(rhs.data);
			}

			//Operators overloads													(Took me a while to readlize that it is needed to use the iterators in here o_O)
			//Copy Assignment Operator
			Image &operator=(const Image &rhs) {
				this->width = rhs.width;
				this->height = rhs.height;
				this->loadImage(rhs.name);
				return *this;
			}

			//Move Assignment Operator
			Image &operator=(Image &&rhs) {
				this->width = rhs.width;
				this->height = rhs.height;
				this->data = std::move(rhs.data);
				return *this;
			}

			//Add two images together.
			Image operator+(const Image &image) {
				Image resultImage(*this);
				if (this->width != image.width || this->height != image.height) {			//checks that the 2 images are the same size. f they are not, notify the user
					std::cout << "Images do not have the same size." << std::endl;
					exit(0);
				}
				resultImage += image;														//Calls the overloaded *= operator
				return resultImage;
			}

			//Add two images together.
			Image operator+=(const Image &image) {
				imageIterator thisImageIterator = this->begin();
				imageIterator otherImageIterator = image.begin();

				while (thisImageIterator != this->end()) {
					if ((*thisImageIterator + *otherImageIterator) > 255) {					//Value (of overloaded + operator) cannot exceed 255
						*thisImageIterator = 255;
					} else {
						*thisImageIterator = *thisImageIterator + *otherImageIterator;				//Calls the overided + operator
					}
					thisImageIterator++;													//Calls the overloaded ++ operator
					otherImageIterator++;													//Calls the overloaded ++ operator
				}

				return *this;
			}

			//Subtract two images from each other.
			Image operator-(const Image &image) {
				Image result(*this);
				if (this->width != image.width || this->height != image.height) {			//checks that the 2 images are the same size. f they are not, notify the user
					std::cout << "Images do not have the same size." << std::endl;
					exit(0);
				}
				result -= image;
				return result;
			}

			//Subtract two images from each other. very similar to the += overload operator...except subtracts
			Image operator-=(const Image &image) {
				imageIterator thisImageIterator = this->begin();
				imageIterator otherImageIterator = image.begin();

				while (thisImageIterator != this->end()) {
					if ((*thisImageIterator - *otherImageIterator) < 0) {					//Value (of overloaded - operator) cannot be less than 0
						*thisImageIterator = 0;
					} else {
						*thisImageIterator = *thisImageIterator - *otherImageIterator;				//Calls the overided - operator
					}
					thisImageIterator++;													//Calls the overloaded ++ operator
					otherImageIterator++;													//Calls the overloaded ++ operator
				}

				return *this;
			}

			//Masking operator. 
			Image operator/(const Image &image) {
				Image result(*this); 
				if (this->width != image.width || this->height != image.height) {			//checks that the 2 images are the same size. f they are not, notify the user
					std::cout << "Images do not have the same size." << std::endl;
					exit(0);
				}

				imageIterator thisImageIterator = result.begin();
				imageIterator otherImageIterator = image.begin();

				while (thisImageIterator != result.end()) {
					if (*otherImageIterator == 0) {											//If the mask's pixel value is 0, the pixel value is set to 0 too.
						*thisImageIterator = 0;
					}
					thisImageIterator++;
					otherImageIterator++;
				}

				return result;
			}

			//Invert operator. 
			Image operator!() {
				Image result(*this); 
				imageIterator thisImageIterator = result.begin();

				while (thisImageIterator != result.end()) {
					*thisImageIterator = (unsigned char) (255 - *thisImageIterator);		//Inverts 'colour' ie: val = val - 255
					thisImageIterator++;
				}

				return result;
			}

			//Threshold operator.
			Image operator*(const int threshold) {
				Image result(*this);	
				imageIterator thisImageIterator = result.begin();

				while (thisImageIterator != result.end()) {
					*thisImageIterator = (unsigned char) ((*thisImageIterator > threshold) ? 255 : 0);	//all pixels > threshold = white, else black
					thisImageIterator++;
				}

				return result;
			}

			//Comparison operator ==
			bool operator==(const Image &image) {										//checks if 2 images are the...well..same image

				if (this->height != image.height || this->width != image.width) {		//does the same as the imagesSameSize() funct...but instead of exiting...returns a bool
					return false;
				}
				
				imageIterator thisImageIterator = this->begin();
				imageIterator otherImageIterator = image.begin();

				while (thisImageIterator != this->end()) {
					if (*thisImageIterator != *otherImageIterator) {
						return false;
					}

					thisImageIterator++;
					otherImageIterator++;
				}
				return true;
			}

			//Chortcut operator to save file to given filename
			void operator>>(const std::string file) {
				this->saveImage(file);
			}

			//Chortcut operator to load file to given filename
			void operator<<(const std::string file) {
				this->loadImage(file);
			}

			class imageIterator
			{
				private:
					unsigned char *pointer;
					int index;
				public://copy construct is public
					//Constructors		
					imageIterator(unsigned char *ptr) : pointer(ptr), index(0) { }		//Starts off at beginning of array
					imageIterator(unsigned char *ptr, int count) : pointer(ptr), index(count) { }//Starts off at a given point in the array.
					imageIterator(const imageIterator &copyIter) : pointer(copyIter.pointer), index(copyIter.index){ }//Copy

					//Overload operators
					imageIterator &operator++() {										//Increment the index by one
						++index;
						return *this;
					}

					// Increment the index of the interator.
					imageIterator operator++(int) {
						imageIterator tempIter(*this);
						operator++();													//Calls the above overriden ++ operator
						return tempIter;
		            }

					unsigned char &operator*() {										//Deref val of array at looc index and returns it
						return pointer[index];
					}

					bool operator!=(const imageIterator &rhs) {							//Does index comparison
						if(index == rhs.index){
							return true;
						}else{
							return false;
						}
					}

					imageIterator &operator=(const imageIterator &rhs) {				//Move assign operator
						this->pointer = std::move(rhs.pointer);
						this->index = rhs.index;
						return *this;
		            }
			};
			// define begin()/end() to get iterator to start and
			// "one-past" end.
			imageIterator begin() const { return imageIterator(this->data.get());}
			imageIterator end() {return imageIterator(this->data.get(), width * height);}
	};
}
#endif
