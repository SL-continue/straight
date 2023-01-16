#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human: public Player{
	public:
	Human(int id);
	Human(shared_ptr<Player> pl);
	virtual bool is_computer() override;
	~Human();
};
#endif
