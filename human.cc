#include "human.h"
Human::Human(int id): Player{id}{}

Human::Human(shared_ptr<Player> pl): Player{pl}{}

bool Human::is_computer(){
	return false;
}

Human::~Human(){}
