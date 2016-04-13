#include "Image.h"

int main(int argc, const char* argv[]) {
	if (argc < 2) {
        std::cout << "Too few arguments." << std::endl;
        return 0;
    }

    std::string command = argv[1];

    string image1Name = argv[2];
    BTHJAC013::Image image1;
    image1 << image1Name;

    BTHJAC013::Image image2;

    std::string outputName = argv[argc-1];
    BTHJAC013::Image outputImage;

    if (command == "-a") { //Add
        image2 << argv[3];
        outputImage = image1 + image2;
    } else if (command == "-s") { //Subtract
        image2 << argv[3];
        outputImage = image1 - image2;
    } else if (command == "-i") { //Invert
        outputImage = !image1;
        outputImage >> outputName;
    } else if (command == "-l") { //Mask
        image2 << argv[3];
        outputImage = image1 / image2;
    } else if (command == "-t") { //Threshold
        int threshold = stoi(argv[3]);
        outputImage = image1 * threshold;
    } else {
        cout << "Command: " << command << " is not recognized as a legitimate command.";
        return 0;
    }
    imgOut >> outputName;
    return 0;
}