#pragma once
#include <iostream>

#define PURE 0

class Player
{
private:
protected:
	
public:
	virtual bool makeDecision()=PURE;
	Player(void);
	~Player(void);
};
