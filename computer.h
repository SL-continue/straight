#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"
class Computer: public Player {
	public:
	Computer(int id);
	Computer(shared_ptr<Player> pl);
	virtual bool is_computer() override;
	~Computer();
};

#endif
