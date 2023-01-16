#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <vector>
#include <memory>
#include "exceptions.h"
#include "pile.h"
#include "computer.h"
#include "human.h"
#include "pub_func.h"
using namespace std;

class Player;

class Subject{
	vector<int> cards;
	vector<shared_ptr<Pile>> piles;
	vector<shared_ptr<Player>> players;
	vector<int> acceptable;
	int played;  // number of cards been player
	int current; // current player id from 1 - 4
	bool hard;
	public:
	 // accepts an array of shared pointers of size 52 (the deck)
	Subject();
	void difficulty_set();
	bool difficulty(string inp);
	void begin(int id);
	void initialize(string inp);
	void shuffle(unsigned seed);
	void start();
	void display();
	vector<int> acceptables();
	void accept(int index);
	bool is_computer(); // if the current player is player
	void move(); // ai moves
	void move(istream * inp);
	void deck_display(); // display the stored cards
	bool end(); // check if the round of the game is ended
	bool over(); // check if the game has ended
	void quit();
	shared_ptr<Pile> which_pile(string c);
	~Subject();
};

#endif
