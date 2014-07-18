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
	lout << "Player " << playerNumber << " plays " << *c << ".\n";
	Logger.flush();
}

void Player::discard(const Card &card)
{
	Card* c = hand->discard(card);
	lout << "Player " << playerNumber << " discards " << *c << ".\n";
	Logger.flush();
}

CommandType ComputerPlayer::act(Table &table, Command &command)
{
	/*
	Card** cards = getCards();
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			if(table.canPlay(*cards[i])) {
				play(table, cards[i]);
				return PLAY;
			}
		}
	}
	
	discard(cards[0]);*/
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
			lout << "This is not a legal play.\n";
			Logger.flush();
		}
		break;
	case DISCARD:
		if(canDiscard(table, c.card)) {
			discard(c.card);
			return c.type;
		}
		else {
			lout << "You have a legal play. You may not discard.\n";
			Logger.flush();
		}
		break;
	case RAGEQUIT:
		lout << "Player " << getPlayerNumber() << " ragequits. A computer will now take over.\n";
		Logger.flush();
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