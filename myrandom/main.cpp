#include "myRandom.h"
#include <iostream>

int main() {
	
	for (int i = 0; i < 16; i++)
		std::cout << myRandom::uniform() << " ";
	std::cout << std::endl;
	for (int i = 0; i < 16; i++)
		std::cout << myRandom::uniform(10) << " ";
	std::cout << std::endl;
}