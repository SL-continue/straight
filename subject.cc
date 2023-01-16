#include "subject.h"
Subject::Subject():played{0},current{1},hard{false}{
	cards.reserve(52);
	for (int i = 0; i < 52; i ++){
		cards.emplace_back(i);
	}
	piles.reserve(4);
	piles.emplace_back(make_shared<Pile>("Club"));
	piles.emplace_back(make_shared<Pile>("Diamond"));
	piles.emplace_back(make_shared<Pile>("Heart"));
	piles.emplace_back(make_shared<Pile>("Spade"));	
}

void Subject::difficulty_set(){
	cout << "Choose ai difficulty" << endl;
	cout << "easy" << endl;
	cout << "hard" << endl;
}

bool Subject::difficulty(string inp){
	if (inp == "hard"){
		hard = true;
		return true;
	}else if (inp == "easy"){
		hard = false;
		return true;
	}else {
		cerr << "Please choose difficulty" << endl;
		return false;
	}
}

void Subject::begin(int id){
	cout << "Is Player" << id << " a human (h) or a computer (c)?" << endl;
} 

void Subject::initialize(string inp){
	if (inp == "h"){
		auto pl = make_shared<Human>(current);
		shared_ptr<Player> pl_p = pl;
		players.emplace_back(pl_p);
	}else if (inp == "c"){
		auto pl = make_shared<Computer>(current);
		shared_ptr<Player> pl_p = pl;
		players.emplace_back(pl_p);
	}else {
		throw InvalidInput(2);
	}
	current += 1;
	if (current == 5) current = 1;
}

void Subject::shuffle(unsigned seed){
	std::default_random_engine rng{seed};
	std::shuffle(cards.begin(),cards.end(),rng);
}

void Subject::start(){
	played = 0;
	acceptable.clear();
	acceptable.emplace_back(6);
	acceptable.emplace_back(19);
	acceptable.emplace_back(32);
	acceptable.emplace_back(45);
	for (auto it = piles.begin(); it != piles.end(); it ++){
		(*it)->clear();
	}
	int copy_start = 0;
	for (unsigned int n = 0; n < 4; n ++){
		players[n]->get_cards(cards,copy_start);
		copy_start += 13;
	}
	for (int i = 0; i < 4; i ++){
		if (players[i]->seven_spade()){
			current = i + 1;
			cout << "A new round begins. It's Player" << current << "'s turn to play." << endl;
		}
	}
}

void Subject::display(){
	cout << "Cards on the table:" << endl;
	for (auto it = piles.begin(); it != piles.end(); it ++){
		(*it)->display();
	}
	players[current - 1]->display(acceptable);
	cout << "player" << current <<"'s turn to move" << endl;
	cout << ">";
}

vector<int> Subject::acceptables(){
	return acceptable;
}

void Subject::accept(int index){
	// modify the acceptable (vector<int>)
	auto iter = find(acceptable.begin(), acceptable.end(), index);
	acceptable.erase(iter);
	if (index % 13 == 0 || index % 13 == 12){
		return;
	}else if (index % 13 == 6){
		acceptable.emplace_back(index - 1);
		acceptable.emplace_back(index + 1);
	}else if (index % 13 < 6){
		acceptable.emplace_back(index - 1);
	}else if (index % 13 > 6){
		acceptable.emplace_back(index + 1);
	}
	sort(acceptable.begin(),acceptable.end());
}

bool Subject::is_computer(){
	return players[current - 1]->is_computer();
}

int best_play(vector<int> cards){
	int to_play = 0;
	int value = 0;
	int this_value = 0;
	for (auto it = cards.begin(); it != cards.end(); it ++){
		this_value = (*it) % 13 + 1; 
		if (this_value > value){
			to_play = (*it);
			value = this_value;
		}
	}
	return to_play;
}

void Subject::move(){
	shared_ptr<Player> ai = players[current - 1];
	vector<int> playable_cards = ai->playable(acceptable);
	if (hard){
		if (playable_cards.empty()){
			ai->discard(true);
		}else {
			int played_card = best_play(playable_cards);
			shared_ptr<Pile> pi = this->which_pile(getSuit(played_card));
			ai->play(played_card, pi);
			this->accept(played_card);
		}
	}else{
		if (playable_cards.empty()){
			ai->discard(false);
		}else {
			int played_card = (*(playable_cards.begin()));
			shared_ptr<Pile> pi = this->which_pile(getSuit(played_card));
			ai->play(played_card, pi);
			this->accept(played_card);
		}
	}
	played ++;
	if (current != 4){
		current ++;
	}else {
		current = 1;
	}
}


void Subject::move(istream * inp){
	string command;
	string str;
	if(getline(*inp,str)){
	}else {
		throw Quit{};
	}
	if (str == "") return;
	istringstream ss{str};
	ss >> command;
	if (command == "play"){
		string card_name;
		ss >> card_name;
		int index;
		index = getCard(card_name);
		if (players[current - 1]->in_hand(index)){
			shared_ptr<Pile> pile = this->which_pile(getSuit(index));
			shared_ptr<Player> pl = players[current - 1];
			vector<int> playable_cards = pl->playable(acceptable);
			if (find(playable_cards.begin(), playable_cards.end(), index) == playable_cards.end()){
				cerr << "This is not a legal play!" << endl;
				return;
			}
			pl->play(index,pile);
			this->accept(index);
			if (current != 4){
				current ++;
			}else {
				current = 1;
			}
			played ++;
		}
	}else if (command == "discard"){
		string card_name;
		ss >> card_name;
		int index;
		index = getCard(card_name);
		if (players[current - 1]->in_hand(index)){
			shared_ptr<Player> pl = players[current - 1];
			vector<int> playable_cards = pl->playable(acceptable);
			if (playable_cards.empty()){
				players[current - 1]->discard(index);
				if (current != 4){
					current ++;
				}else {
					current = 1;
				}
				played ++;
			}else {
				cerr << "You have a legal play. You may not discard." << endl;
			}
		}
	}else if (command == "deck"){
		this->deck_display();
	}else if (command == "change"){
		string player_name;
		ss >> player_name;
		if (player_name.length() != 7){
			cerr << "Please input \"change player(id)\"." << endl;
			return;
		} 
		char idc = player_name[6];
		if (idc > '0' && idc <= '9'){
			if (idc >= '5'){
				cerr << "There is no player" << idc << "."  << endl;
				return;
			}
		}else {
			cerr << "This is not a player name." << endl;
			return;
		}
		int id = idc - '0';
		if (players[id - 1]->is_computer()){
			shared_ptr<Player> now = players[id - 1];
			auto copy = make_shared<Human>(now);
			players[id - 1] = copy;
			cout << "Player" << id << " joined the game!" << endl;
		}else {
			cerr << "Player" << id << " is human!" << endl;
		}
	}else if (command == "quit"){
		this->quit();
	}else if (command == "ragequit"){
		shared_ptr<Player> now = players[current - 1];
		auto copy =  make_shared<Computer>(now);
		players[current - 1] = copy;
		cout << "Player" << current << " ragequits, A computer will now take over." << endl;
	}else if (command == "restart"){
		int restarted = players[current - 1]->restarted();
		players[current - 1]->restart();
		if (restarted == 1){
			cout << "You have restarted" << endl;
			return;
		}else if (restarted >= 2){
			this->move();
			return;
		}
		int count = 1;
		int humans = 1;
		string agreement {""};
		for (int i = 0; i < 4; i ++){
			if (i + 1 != current && !(players[i]->is_computer())){
				humans ++;
				cout << "Do you player" << i + 1 << " agree to restart? (y or n)" << endl;
				getline(*inp,agreement);
				if (agreement == "y"){
					count ++;
				}else if (agreement == "n"){
				}else {
					cerr << "Please input your agreement" << endl;
					i --;
				}
			}
		}
		if (count > humans / 2){
			throw Restart{};
		}else {
			cout << "restart not agreed" << endl;
		}
	}else {
		throw InvalidInput(2);
	}
}

void Subject::deck_display(){
	int count = 0;
	for (auto it = cards.begin(); it != cards.end(); it ++){
		cout << " " << getName((*it));
		if (count == 12){
			count = -1;
			cout << endl;
		}
		count ++;
	}
}

bool Subject::end(){
	return (played == 52)? true:false;
}

bool Subject::over(){
	int add;
	int res[4];
	bool over = false;
	for (int i = 0; i < 4; i ++){
		players[i]->display_discards();
		int before = players[i]->get_score();
		add = players[i]->addscore();
		cout << "Player" << players[i]->get_id() << "'s score: " << before << " + " << add << " = " << players[i]->get_score() << endl;
		if (players[i]->get_score() > 80){
			over = true;
		}
		res[i] = players[i]->get_score();
	}
	if (over){
		int winner_score = *min_element(res,res+4);
		for (int i = 0; i < 4; i ++){
			if (res[i] == winner_score){
				cout << "Player" << i + 1 << " wins" << endl;
			}
		}
	}
	return over;
}

void Subject::quit(){
	throw Quit{};
}

Subject::~Subject(){}

shared_ptr<Pile> Subject::which_pile(string c){
	if (c == "C"){
		return piles[0];
	}else if (c == "D"){
		return piles[1];
	}else if (c == "H"){
		return piles[2];
	}else if (c == "S"){
		return piles[3];
	}else{
		throw InvalidInput(1);
	}
}
	
