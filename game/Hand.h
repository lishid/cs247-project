#ifndef _HAND_
#define _HAND_

#include "Card.h"
#include "Table.h"

class Hand {
public:
	Hand();
	Hand(Hand *hand);
	virtual ~Hand();
	void deal(Card * const *newCards);
	void reset();
	void endRound();
	Card *play(const Card &card);
	Card *discard(const Card &card);
	int getScore() const;
	int getDiscards() const;
	Card *getCard(int cardNumber) const;
	bool canPlay(const Table &table, const Card &card) const;
	bool canDiscard(const Table &table, const Card &card) const;
private:
	int score;
	Card *cards[RANK_COUNT];
	Card *discards[RANK_COUNT];
	Card *remove(const Card &card);
	void clear();
};

#endif