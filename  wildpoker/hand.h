#pragma once

class Hand
{
private:
	Card * playerCards[3];
	Card * comunityCards[2];
protected:

public:
	Hand(void);
	~Hand(void);
};
