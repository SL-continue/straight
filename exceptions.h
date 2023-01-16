#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <string>
#include <iostream>
class InvalidInput{
	// different types of invalid input have different number
	// 1 represents wrong input of cards like BC
	// 2 represents wrong command
	int type; 
	public:
	InvalidInput(int t);
	void print();
};

class Quit{
	// special exception for quit which stops the game
};

// special exception for restart
class Restart{};

#endif
