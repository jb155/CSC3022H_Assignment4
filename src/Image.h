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

namespace BTHJAC013 {
	class Image
	{
		private:
			std::string name; 														//Name of the image bieng processed
			int width, height;														//Pixel dimensions of the image bieng read
			std::unique_ptr<unsigned char[]> data;									//Data of the buffered image
		public:
			Image(){}
			Image(std::string fileName){
				if(!loadImage(fileName)){
					std::cout<<"Could not successfully load in image " + fileName << std::endl;
				}
			}
			~Image();

			bool loadImage(std::string file);										//load the image file in. Save/parse to the data var
			//void save(std::string file);											//save the image data to given file name

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
				this->imageData = std::move(rhs.imageData);
			}

			//Operators overloads		(Took me a while to readlize that it is needed to use the iterators in here o_O)
			//Copy Assignment Operator
			Image &operator=(const Image &rhs) {
				this->width = rhs.width;
				this->height = rhs.height;
				this->load(rhs.filename);
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
			Image operator+=(const Image &image) {
				Image result(*this);
				return result;
			}

			//Add two images together.
			Image operator+(const Image &image) {
				Image result(*this);
				return result;
			}

			//Subtract two images from each other.
			Image operator-=(const Image &image) {
				Image result(*this);
				return result;
			}

			//Subtract two images from each other.
			Image operator-(const Image &image) {
				Image result(*this);
				return result;
			}

			//Masking operator. 
			Image operator/(const Image &image) {
				Image result(*this); //If the mask's pixel value is 0, the pixel value is set to 0 too.
				return result;
			}

			//Invert operator. 
			Image operator!() {
				Image result(*this); //p = (255 - p)
				return result;
			}

			//Threshold operator.
			Image operator*(const int threshold) {
				Image result(*this);	//Turns all pixels that surpass the given threshold white, everything else black.
				return result;
			}

			//Comparison operator ==
			bool operator==(const Image img) {
				return true;
			}

			//Chortcut operator to save file to given filename
			void operator>>(const std::string fileName) {
				this->save(file);
			}

			//Chortcut operator to load file to given filename
			void operator<<(const std::string fileName) {
				this->loadFile(file);
			}

			class imageIterator
			{
				private:
					unsigned char *ptr;
					// construct only via Image class (begin/end)
					imageIterator(u_char *p) : ptr(p) {}
				public://copy construct is public
					//Constructors
					imageIterator( const imageIterator & rhs) : ptr(rhs.ptr) {}			
					imageIterator(unsigned char *ptr) : pointer(ptr), index(0) { }	//Starts off at beginning of array
					imageIterator(unsigned char *ptr, int count) : pointer(ptr), index(count) { }//Starts off at a given point in the array.
					imageIterator(const imageIterator &copyIter) : pointer(copyIter.pointer), index(copyIter.index){ }//Copy

					//Overload operators
					imageIterator &operator++() {								//Increment the index by one
						++index;
						return *this;
					}

					/*// Increment the index of the interator.
					imageIterator operator++(int) {
						imageIterator tempIter(*this);
						operator++();
						return tempIter;
		            }*/

					imageIterator &operator--() {								//Reduce the index by one
						--index;
						return *this;
					}

					/*// Decrement the index of the interator.
					imageIterator operator--(int) {
						imageIterator tempIter(*this);
						operator--();
						return tempIter;
					}*/

					unsigned char &operator*() {							//Deref val of array at looc index and returns it
						return pointer[index];
					}

					bool operator!=(const imageIterator &rhs) {					//Does index comparison
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
			imageIterator begin(void) { return imageIterator(data.get())} // etc
			imageIterator end(void) {return imageIterator(this->imageData.get(), width * height)}
	};
}
#endif
