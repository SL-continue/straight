#include "computer.h"
Computer::Computer(int id): Player{id}{}

Computer::Computer(shared_ptr<Player> pl): Player{pl}{}

bool Computer::is_computer(){
	return true;
}

Computer::~Computer(){}

