#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <cstring>
#include <random>
#include <algorithm>
#include <vector>
#include <memory>
#include "subject.h"
#include "exceptions.h"
using namespace std;

// includes here
bool allnum(char* argu); 

int main(int argc, char* argv[]){
	// Turns on the raising of exceptions when the fail or the eof bit get set for std::cin
	string command;
	cin.exceptions(ios::eofbit|ios::failbit);
	try{
			string difficult;
			unsigned seed = 0;
			if (argc == 1){
				seed = std::chrono::system_clock::now().time_since_epoch().count();
			}else if (argc == 2){
				if (!(allnum(argv[1]))){
					cerr << "The argument is not a seed" << endl;
					return 1;
				}else {
					seed =(unsigned) atoi(argv[1]);
				}
			}else {
				cerr << "Wrong number of arguments" << endl;
				throw Quit{};
			}
			auto s = make_shared<Subject>();
			while(true){
				s->difficulty_set();
				cin >> command;
				if(s->difficulty(command)){
					break;
				}
			}
			// initialize for computer and human players
			for (int i = 1; i <= 4; i ++){
				s->begin(i);
				try{
					cin >> command;  // input is 'h' or 'c'
					s->initialize(command);		
				}catch (InvalidInput){
					i --;
					cerr << "Invalid type of player, please enter again" << endl;
				}	
			}
			// game starts after shuffled
			s->shuffle(seed);
			s->start();
			// there is a "" in cin)
			// use this to remove the ""
			s->move(& cin);
			// move the board until the game ends 
			while (true){
				if (s->is_computer()){
					s->move();
				}else {
					s->display();
					try{
						s->move(& cin);
					}catch (InvalidInput & er){
						er.print();
						continue;
					}catch (Quit){
						s->over();
						break;
					}catch(Restart){
						s->shuffle(seed);
						s->start();
						continue;
					}
				}
				if (s->end()){
					if (s->over()){
						break;
					}else {
						s->shuffle(seed);
						s->start();
					}
				}
			}
		} catch (ios::failure) {}
	return 0;
}

bool allnum(char* argu){
	for (unsigned int i = 0; i < strlen(argu); i ++){
		if (argu[i] >= '0' && argu[i] <= '9'){
			continue;
		}else{
			return false;
		}
	}
	return true;
}
