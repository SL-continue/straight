#include "pub_func.h"

string getRank(int index){
	if (index % 13== 0){
		return "A";
	}else if (index % 13 == 9){
		return "T";
	}else if (index % 13 == 10){
		return "J";
	}else if (index % 13 == 11){
		return "Q";
	}else if (index % 13 == 12){
		return "K";
	}else {
		return to_string(index % 13 + 1);
	}
	return "";
}

string getSuit(int index){
	if (index / 13 == 0){
		return "C";
	}else if (index / 13 == 1){
		return "D";
	}else if (index / 13 == 2){
		return "H";
	}else if (index / 13 == 3){
		return "S";
	}
	return "";
}

string getName(int index){
	string f {""};
	f.append(getRank(index));
	f.append(getSuit(index));
	return f;
}

int getCard(string name){
	char first_char = name[0];
	char second_char = name[1];
	int index = 0;
	if (first_char == 'A'){
		index += 0;
	}else if (first_char == 'T'){
		index += 9;
	}else if (first_char == 'J'){
		index += 10;
	}else if (first_char == 'Q'){
		index += 11;
	}else if (first_char == 'K'){
		index += 12;
	}else if (first_char <= '9' && first_char > '1'){
		index += (int) (first_char - '0') - 1;
	}else { // exceptions of wrong input of card
		throw InvalidInput(1);
	}
	if (second_char == 'C'){
	}else if (second_char == 'D'){
		index += 13;
	}else if (second_char == 'H'){
		index += 26;
	}else if (second_char == 'S'){
		index += 39;
	}else{
		throw InvalidInput(1);
	}
	return index;
}

