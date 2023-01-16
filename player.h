#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>
#include "pub_func.h"
#include "pile.h"
#include "exceptions.h"
using namespace std;

class Player{
	public:
	Player(int id);
	Player(shared_ptr<Player> pl);
	void get_cards(vector<int> & cards, int start_index);
	bool seven_spade();
	void play(int c, shared_ptr<Pile> p);
	vector<int> playable(vector<int> accepts);
	void discard(bool hard);
	bool in_hand(int c);
	void discard(int c);
	int addscore();
	void display(vector<int> accepts);
	void display_discards();
	int get_score();
	int get_id();
	vector<int> get_cards();
	vector<int> get_discards();
	void restart();
	int restarted();
	virtual bool is_computer() = 0;
	virtual ~Player();
	protected:
	int id;
	int score;
	int restart_time;
	vector<int> hands;
	vector<int> discards;
};


#endif
