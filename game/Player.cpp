#include "Player.h"

using namespace std;


Player::Player(int n, Hand *h) : playerNumber(n), hand(h)
{

}

Player::Player(Player *player) : playerNumber(player->playerNumber), hand(player->hand)
{
	delete player;
}

Player::~Player()
{

}

int Player::getPlayerNumber() const
{
	return playerNumber;
}

Card *Player::getCard(int cardNumber) const
{
	return hand->getCard(cardNumber);
}

bool Player::canPlay(const Table &table, const Card &card) const
{
	return hand->canPlay(table, card);
}

bool Player::canDiscard(const Table &table, const Card &card) const
{
	return hand->canDiscard(table, card);
}

void Player::play(Table &table, const Card &card)
{
	Card* c = hand->play(card);
	table.play(*c);
	lout << "Player " << playerNumber << " plays " << *c << "." << lend;
}

void Player::discard(Table &table, const Card &card)
{
	Card* c = hand->discard(card);
	table.discard(*c);
	lout << "Player " << playerNumber << " discards " << *c << "." << lend;
}


CommandType ComputerPlayer::act(Table &table, Command &command)
{
	if(command.type != AI) {
		return BAD;
	}

	Card *largestPlayable = NULL;
	Card *smallest = NULL;

	for(int i = 0; i < RANK_COUNT; i++) {
		Card *card = getCard(i);
		if(card != NULL) {
			if(smallest == NULL) {
				smallest = card;
			}
			else if(card->getScore() < smallest->getScore()) {
				smallest = card;
			}

			if(canPlay(table, *card)) {

				if(largestPlayable == NULL) {
					largestPlayable = card;
				}
				else if(card->getScore() > largestPlayable->getScore()) {
					largestPlayable = card;
				}
			}
		}
	}

	if(largestPlayable != NULL) {
		play(table, *largestPlayable);
		return PLAY;
	}
	
	discard(table, *smallest);
	return DISCARD;
}

bool ComputerPlayer::isHuman() const
{
	return false;
}

CommandType HumanPlayer::act(Table &table, Command &c)
{
	switch(c.type) {
	case PLAY:
		if(canPlay(table, c.card)) {
			play(table, c.card);
			return c.type;
		}
		else {
			lerr << "This is not a legal play." << lend;
		}
		break;
	case DISCARD:
		if(canDiscard(table, c.card)) {
			discard(table, c.card);
			return c.type;
		}
		else {
			lerr << "You have a legal play. You may not discard." << lend;
		}
		break;
	case RAGEQUIT:
		lout << "Player " << getPlayerNumber() << " ragequits. A computer will now take over." << lend;
		return c.type;
		break;
	default:
		break;
	}
	return BAD;
}

bool HumanPlayer::isHuman() const
{
	return true;
}