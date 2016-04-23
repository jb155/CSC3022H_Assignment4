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
			~Image();

			void load(std::string file);											//load the image file in. Save/parse to the data var
			//void save(std::string file);											//save the image data to given file name

			std::string getName(void){return name;}

			// Copy Constructor														//Was told it's good practice to do this, even if it wont be used
			Image(const Image &rhs) {
				this->filename = rhs.filename;
				this->width = rhs.width;
				this->height = rhs.height;
				this->load(this->filename);
			}

			// Move Constructor														//Was told it's good practice to do this, even if it wont be used
			Image(Image &&rhs) {
				this->filename = std::move(rhs.filename);
				this->width = rhs.width;
				this->height = rhs.height;
				this->imageData = std::move(rhs.imageData);
			}

			class iterator
			{
				private:
					unsigned char *ptr;
					// construct only via Image class (begin/end)
					iterator(u_char *p) : ptr(p) {}
				public://copy construct is public
					//Constructors
					iterator( const iterator & rhs) : ptr(rhs.ptr) {}			
					iterator(unsigned char *ptr) : pointer(ptr), index(0) { }	//Starts off at beginning of array
					iterator(unsigned char *ptr, int count) : pointer(ptr), index(count) { }//Starts off at a given point in the array.
					iterator(const iterator &copyIter) : pointer(copyIter.pointer), index(copyIter.index){ }//Copy

					//Overload operators
					iterator &operator++() {								//Increment the index by one
						++index;
						return *this;
					}

					/*// Increment the index of the interator.
					iterator operator++(int) {
						iterator tempIter(*this);
						operator++();
						return tempIter;
		            }*/

					iterator &operator--() {								//Reduce the index by one
						--index;
						return *this;
					}

					/*// Decrement the index of the interator.
					iterator operator--(int) {
						iterator tempIter(*this);
						operator--();
						return tempIter;
					}*/

					unsigned char &operator*() {							//Deref val of array at looc index and returns it
						return pointer[index];
					}

					bool operator!=(const iterator &rhs) {					//Does index comparison
						if(index == rhs.index){
							return true;
						}else{
							return false;
						}
					}

					iterator &operator=(const iterator &rhs) {				//Move assign operator
						this->pointer = std::move(rhs.pointer);
						this->index = rhs.index;
						return *this;
		            }
			};
			// define begin()/end() to get iterator to start and
			// "one-past" end.
			iterator begin(void) { return iterator(data.get())} // etc
			iterator end(void) {return iterator()}
	};
}
#endif
