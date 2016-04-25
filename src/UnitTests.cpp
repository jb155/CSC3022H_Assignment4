/*                                /   \       
 _                        )      ((   ))     (
(@)                      /|\      ))_((     /|\
|-|                     / | \    (/\|/\)   / | \                      (@)
| | -------------------/--|-voV---\`|'/--Vov-|--\---------------------|-|
|-|  UnitTests.cpp          '^`   (o o)  '^`              04-04-2016  | |
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
#include "Image.h"

#define CATCH_CONFIG_MAIN

#include <string>
#include <iostream>
#include <memory>

#include "catch.hpp"

BTHJAC013::Image mainImg("shrek_rectangular.pgm");
BTHJAC013::Image mask("donkey_mask.pgm");
BTHJAC013::Image temp;

TEST_CASE("Test Adding", "[add]") {
	std::cout << "0" << std::endl;
    temp << "Tests/AdditionTest.pgm";
    REQUIRE((mainImg + mask) == temp);
}

TEST_CASE("Test Subtracting", "[subtract]") {
	std::cout << "1" << std::endl;
    temp << "Tests/SubtractionTest.pgm";
    REQUIRE((mainImg - mask) == temp);
}

TEST_CASE("Test Inverting", "[invert]") {
	std::cout << "2" << std::endl;
    temp << "Tests/InversionTest.pgm";
    REQUIRE(!mask == temp);
}

TEST_CASE("Test Masking", "[mask]") {
	std::cout << "3" << std::endl;
    temp << "Tests/MaskingTest.pgm";
    REQUIRE((mainImg / mask) == temp);
}

TEST_CASE("Test Threshold", "[threshold]") {
	std::cout << "4" << std::endl;
    temp << "Tests/ThresholdTest(200).pgm";
    REQUIRE((mainImg * 200) == temp);
}

TEST_CASE("Test Save", "[save]") {
	std::cout << "4" << std::endl;
    temp << "Tests/SavingTest.pgm";
    REQUIRE((mainImg + mask) == temp);
    (mainImg + mask) >> "Tests/SavingTest.pgm";
    temp << "Tests/SavingTest.pgm";
    REQUIRE((mainImg + mask) == temp);
}

TEST_CASE("Test Iterator", "[iterator]") {
	std::cout << "5" << std::endl;
    temp << "Tests/SavingTest.pgm";
    REQUIRE((mainImg + mask) == temp);
    BTHJAC013::Image::imageIterator tempIter = temp.begin();
    BTHJAC013::Image temp2;
    temp2 = mainImg + mask;
    BTHJAC013::Image::imageIterator maskIter = temp2.begin();

    bool allEqual = true;
    while (tempIter != temp.end()) {
        if (*tempIter != *maskIter) {
            allEqual = false;
            break;
        }
        tempIter++;
        maskIter++;
    }
    REQUIRE(allEqual);
}