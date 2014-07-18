#include "Hand.h"

using namespace std;

Hand::Hand() : score(0)
{
	clear();
}

Hand::Hand(Hand *hand) : score(hand->score)
{
	for(int i = 0; i < RANK_COUNT; i++) {
		cards[i] = hand->cards[i];
		discards[i] = hand->discards[i];
	}
}

Hand::~Hand()
{

}

void Hand::deal(Card * const *newCards)
{
	for(int i = 0; i < RANK_COUNT; i++) {
		cards[i] = newCards[i];
	}
}

void Hand::endRound()
{
	int roundScore = 0;

	for(int i = 0; i < RANK_COUNT; i++) {
		if(discards[i] != NULL) {
			roundScore += discards[i]->getScore();
		}
	}
	
	score = score + roundScore;

	clear();
}

Card *Hand::play(const Card &card)
{
	return remove(card);
}

Card *Hand::discard(const Card &card)
{
	Card *c = remove(card);
	for(int i = 0; i < RANK_COUNT; i++) {
		if(discards[i] == NULL) {
			discards[i] = c;
			break;
		}
	}
	return c;
}

int Hand::getScore() const
{
	return score;
}

int Hand::getDiscards() const
{
	int count = 0;
	for(int i = 0; i < RANK_COUNT; i++) {
		if(discards[i] != NULL) {
			count++;
		}
	}
	return count;
}

Card *Hand::getCard(int cardNumber) const
{
	return cards[cardNumber];
}

bool Hand::canPlay(const Table &table, const Card &card) const
{
	//Ensure card can be played
	if(!table.canPlay(card)) {
		return false;
	}

	//Ensure player has card
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL && *cards[i] == card) {
			return true;
		}
	}

	return false;
}

bool Hand::canDiscard(const Table &table, const Card &card) const
{
	bool hasCard = false;
	//Ensure player has card and can't play other cards
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			//Ensure no cards can be played
			if(table.canPlay(*cards[i])) {
				return false;
			}

			if(*cards[i] == card) {
				hasCard = true;
			}
		}
	}
	return hasCard;
}

Card *Hand::remove(const Card &card)
{
	Card *cardPtr = NULL;
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL && *cards[i] == card) {
			cardPtr = cards[i];
			cards[i] = NULL;
			break;
		}
	}
	return cardPtr;
}

void Hand::clear()
{
	for(int i = 0; i < RANK_COUNT; i++) {
		cards[i] = NULL;
		discards[i] = NULL;
	}
}
