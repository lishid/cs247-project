#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Table.h"
#include "Command.h"
#include "Hand.h"

#include "../ui/Log.h"

class Player {
public:
	Player(int playerNumber, Hand *h);
	Player(Player *player);
	virtual ~Player();
	virtual CommandType act(Table &table, Command &command) = 0;
	virtual bool isHuman() const = 0;
	int getPlayerNumber() const;
private:
	const int playerNumber;
	Hand *hand;
protected:
	Card *getCard(int cardNumber) const;
	bool canPlay(const Table &table, const Card &card) const;
	bool canDiscard(const Table &table, const Card &card) const;
	void play(Table &table, const Card &card);
	void discard(Table &table, const Card &card);
};

class ComputerPlayer : public Player {
public:
	ComputerPlayer(int playerNumber, Hand *h) : Player(playerNumber, h) {};
	ComputerPlayer(Player *player) : Player(player) {};
	CommandType act(Table &table, Command &command);
	bool isHuman() const;
};

class HumanPlayer : public Player {
public:
	HumanPlayer(int playerNumber, Hand *h) : Player(playerNumber, h) {};
	CommandType act(Table &table, Command &command);
	bool isHuman() const;
};

#endif
