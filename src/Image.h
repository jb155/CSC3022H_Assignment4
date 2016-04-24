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
