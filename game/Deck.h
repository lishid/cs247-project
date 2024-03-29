#ifndef _DECK_
#define _DECK_

#include "Card.h"
#include "../ui/Log.h"

class Deck {
public:
	Deck();
	virtual ~Deck();
	
	void shuffle(); //Shuffle the deck
	Card * const *deal(int player) const; //Deal cards for player
	int findStartingPlayer() const; //Find the player who has the 7 of spades
	void print() const; //Debug print the deck

	static const int DECK_SIZE = SUIT_COUNT * RANK_COUNT;
private:
	Card *cards[DECK_SIZE];
};

#endif
