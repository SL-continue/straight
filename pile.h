#ifndef _PILE_H_
#define _PILE_H_

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "pub_func.h"
using namespace std;

class Pile{
	string suit_name;
	vector<int> cards;
	public:
	Pile(string name);
	void add(int c);
	void display();
	void clear();
	~Pile();
};

#endif
