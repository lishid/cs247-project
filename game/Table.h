#ifndef _TABLE_
#define _TABLE_

#include "Deck.h"

using namespace std;

class Table {
public:
	Table();
	virtual ~Table();
	void reset();
	void play(const Card &card);
	bool canPlay(const Card &card) const;
	void print() const;
	bool played(const Card &card) const;
	bool isLastCard(const Card &card) const;
private:
	const Card *lastCard;
	bool cards[Deck::DECK_SIZE]; //Cards that has been played
	bool playable[Deck::DECK_SIZE]; //Cards that can be played
};

#endif
