#include "pile.h"

Pile::Pile(std::string name): suit_name{name}{}

void Pile::add(int c){
	if (cards.empty()){
		cards.emplace_back(c);
	}else if (c < (*cards.begin())){
		cards.insert(cards.begin(),c);
	}else {
		cards.emplace_back(c);
	}
}

void Pile::display(){
	std::cout << suit_name << ":";
	for (auto i = cards.begin(); i != cards.end(); i ++){
		std::cout << " " << getRank((*i));
	}
	std::cout << std::endl;
}

void Pile::clear(){
	cards.clear();
}

Pile::~Pile(){
	cards.clear();
}	
