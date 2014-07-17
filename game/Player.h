#ifndef _PLAYER_
#define _PLAYER_

#include "Card.h"
#include "Table.h"
#include "Command.h"
#include <vector>
#include <iostream>

using namespace std;

class Player {
public:
	Player(int playerNumber);
	virtual ~Player();
	virtual Type turn(Table &table, bool print) = 0;
	int endRound();
	int getScore() const;
	int getPlayerNumber() const;
	Card **getCards();
private:
	const int playerNumber;
	int score;
	Card *cards[RANK_COUNT];
	Card *discards[RANK_COUNT];
	Card *remove(Card *card);
	void clear();
protected:
	Player(Player *player);
	void play(Table &table, Card *card);
	void discard(Card *card);
	void printHand() const;
	void printLegalPlays(const Table &table) const;
	bool canPlay(const Table &table, const Card *card) const;
	bool canDiscard(const Table &table, const Card *card) const;
};

class ComputerPlayer : public Player {
public:
	ComputerPlayer(int playerNumber);
	ComputerPlayer(Player *player);
	Type turn(Table &table, bool print);
};

class HumanPlayer : public Player {
public:
	HumanPlayer(int playerNumber);
	Type turn(Table &table, bool print);
};

#endif
