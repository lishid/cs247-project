#include "Deck.h"
#include <iostream>
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
	int n = Deck::DECK_SIZE;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards[n];
		cards[n] = cards[k];
		cards[k] = c;
	}
}

vector<Card*> Deck::deal(int player) const
{
	vector<Card*> v;
	for(int i = player * RANK_COUNT; i < (player + 1) * RANK_COUNT; i++) {
		v.push_back(cards[i]);
	}
	return v;
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

void Deck::print() const
{
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			cout << *cards[RANK_COUNT * i + j];
			if(j < RANK_COUNT - 1) {
				cout << " ";
			}
			else {
				cout << endl;
			}
		}
	}
}