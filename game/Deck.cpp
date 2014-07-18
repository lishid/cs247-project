#include "Deck.h"
#include <cstdlib>

using namespace std;

Deck::Deck()
{
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			cards[13 * i + j] = new Card(Suit(i), Rank(j)); 
		}
	}
}

Deck::~Deck()
{
	for(int i = 0; i < Deck::DECK_SIZE; i++) {
		delete cards[i];
	}
}

void Deck::shuffle()
{
	lout << "Shuffling the deck..." << lend;
	int n = Deck::DECK_SIZE;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards[n];
		cards[n] = cards[k];
		cards[k] = c;
	}
}

Card * const *Deck::deal(int player) const
{
	int offset = player * RANK_COUNT;
	return cards + offset;
}

int Deck::findStartingPlayer() const
{
	for(int i = 0; i < Deck::DECK_SIZE; i++) {
		if(cards[i]->getSuit() == SPADE && cards[i]->getRank() == SEVEN) {
			return i / RANK_COUNT;
		}
	}
	return -1;
}