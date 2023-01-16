#ifndef _PUB_FUNC_H_
#define _PUB_FUNC_H_
#include <string>
#include <cstring>
#include <vector>
#include "exceptions.h"
using namespace std;

string getRank(int index);

string getSuit(int index);

string getName(int index);

int getCard(string name);

#endif
