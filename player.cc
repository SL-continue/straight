#include "player.h"

Player::Player(int id):id{id},score{}{}

Player::Player(shared_ptr<Player> pl):id{pl->get_id()},score{pl->get_score()},hands{pl->get_cards()},discards{pl->get_discards()}{}

void Player::get_cards(vector<int> &cards, int start_index){
	hands.clear();
	discards.clear();
	for (int i = start_index; i < start_index + 13; i ++){
		hands.emplace_back(cards[i]);
	}
	sort(hands.begin(),hands.end());
}

bool Player::seven_spade(){
	for (auto it = hands.begin(); it != hands.end(); it ++){
		if ( (*it) == 45) return true;
	}
	return false;
}

void Player::play(int c, shared_ptr<Pile> p){
	int index = c;
	p->add(index);
	hands.erase(find(hands.begin(),hands.end(),index));
	cout << "Player" << id << " plays " << getName(index) << endl;
}

vector<int> Player::playable(vector<int> accepts){
	vector<int> playables;
	for (auto it = hands.begin(); it != hands.end(); it ++){
		if (find(accepts.begin(),accepts.end(),(*it)) != accepts.end()){
			playables.emplace_back((*it));
		}
	}
	return playables;
}

int best_discard(vector<int> & cards){
	int to_discard = 0;
	int value = 14;
	int this_value = 0;
	for (auto it = cards.begin(); it != cards.end(); it ++){
		this_value = (*it) % 13 + 1;
		if (this_value < value){
			to_discard = (*it);
			value = this_value;
		}
	}
	return to_discard;
}

void Player::discard(bool hard){
	int c;
	if (hard){
		c = best_discard(hands);
	}else {
		c = (*hands.begin());
	}
	this->discard(c);
}

bool Player::in_hand(int c){
	if (find(hands.begin(),hands.end(),c) == hands.end()){
		cerr << "This card is not in your hand!" << endl;
		return false;
	}
	return true;
}

void Player::discard(int index){
	if (discards.empty()){
		discards.emplace_back(index);
		hands.erase(find(hands.begin(), hands.end(), index));
	}else {
		for (auto i = discards.begin();;i ++){
			if (index < (*i)){
				discards.insert(i,index);
				hands.erase(find(hands.begin(),hands.end(),index));
				break;
			}else if (i == discards.end()){
				discards.emplace_back(index);
				hands.erase(find(hands.begin(),hands.end(),index));
				break;
			}
		}
	}
	cout << "Player" << id << " discards " << getName(index) << endl;
}

int Player::addscore(){
	int adds = 0;
	for (auto i = discards.begin(); i != discards.end(); i ++){
		adds += (*i)%13 + 1;
	}
	score += adds;
	return adds;
}


void Player::display(vector<int> accepts){
	cout << "Your hand:";
	for (auto it = hands.begin(); it != hands.end(); it ++){
		cout << " " << getName((*it));
	}
	cout << endl;
	vector<int> playables = this->playable(accepts);
	cout << "Legal plays:";
	for (auto it = playables.begin(); it != playables.end(); it ++){
		cout << " " << getName((*it));
	}
	cout << endl;
}

void Player::display_discards(){
	cout << "Player" << id << "'s discards:";
	for (auto it = discards.begin(); it != discards.end(); it ++){
		cout << " " << getName((*it));
	}
	cout << endl;
} 

int Player::get_score(){
	return score;
}

int Player::get_id(){
	return id;
}

vector<int> Player::get_cards(){
	return hands;
}

vector<int> Player::get_discards(){
	return discards;
}

void Player::restart(){
	restart_time ++;
}

int Player::restarted(){
	return restart_time;
}

Player::~Player(){
	hands.clear();
	discards.clear();
}

