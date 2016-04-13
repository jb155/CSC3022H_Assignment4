#ifndef IMAGE_H
#define IMAGE_H
namespace BTHJAC013 {
	class Image
	{
		private:
			int width, height;
			std::unique_ptr<unsigned char[]> data;
		public:
			class iterator
			{
				private:
					unsigned char *ptr;
					// construct only via Image class (begin/end)
					iterator(u_char *p) : ptr(p) {}
				public://copy construct is public
					iterator( const iterator & rhs) : ptr(rhs.ptr) {}
					// define overloaded ops: *, ++, --, =
					iterator & operator=(const iterator & rhs)
					{...}
					// other methods for iterator
			};
			// define begin()/end() to get iterator to start and
			// "one-past" end.
			iterator begin(void) { return iterator(data.get())} // etc
	};
}
#endif
