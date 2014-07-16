#include "Table.h"
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

Table::Table()
{
	reset();
}

Table::~Table()
{

}

void Table::reset()
{
	for (int i = 0; i < Deck::DECK_SIZE; i++) {
		cards[i] = false;
	}
	for (int i = 0; i < Deck::DECK_SIZE; i++) {
		playable[i] = false;
	}
	playable[SPADE * RANK_COUNT + SEVEN] = true;
}

void Table::play(const Card &card)
{
	assert(canPlay(card));
	int suit = card.getSuit();
	int rank = card.getRank();
	//Play the card
	cards[suit * RANK_COUNT + rank] = true;

	//Played the first card, update all sevens
	if(suit == SPADE && rank == SEVEN) {
		for(int i = 0; i < SUIT_COUNT; i++) {
			playable[i * RANK_COUNT + SEVEN] = true;
		}
	}

	//Update the playable cache
	if(rank > ACE) {
		playable[suit * RANK_COUNT + rank - 1] = true;
	}
	if(rank < KING) {
		playable[suit * RANK_COUNT + rank + 1] = true;
	}
}

bool Table::canPlay(const Card &card) const
{
	int suit = card.getSuit();
	int rank = card.getRank();
	int index = suit * RANK_COUNT + rank;
	
	//Playable and haven't been played yet
	return playable[index] && !cards[index];
}

void Table::print() const
{
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

	cout << "Cards on the table:" << endl;
	for(int i = 0; i < SUIT_COUNT; i++) {
		//Print title
		if(i == CLUB) cout << "Clubs";
		if(i == DIAMOND) cout << "Diamonds";
		if(i == HEART) cout << "Hearts";
		if(i == SPADE) cout << "Spades";
		cout << ":";
		for(int j = 0; j < RANK_COUNT; j++) {
			if(!cards[i * RANK_COUNT + j]) continue;
			cout << " ";
			cout << ranks[j];
		}
		cout << endl;
	}
}
