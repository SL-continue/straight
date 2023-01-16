#include "exceptions.h"

InvalidInput::InvalidInput(int t):type{t}{}

void InvalidInput::print(){
	if (type == 1){
		std::cout << "Invalid card" << std::endl;
	}else {
		std::cout << "Invalid command" << std::endl;
	}
}
