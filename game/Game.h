#ifndef _GAME_
#define _GAME_

#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include "../abstract/Subject.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

class Game : public Subject {
public:
	Game();
	virtual ~Game();
	void run();

	//Getters
	const Table *getTable() const;
	const Player *getPlayer(int number) const;
	int getCurrentPlayer() const;
	double getProgress() const;
private:
	Deck deck; //The deck for shuffle and dealing
	Table table; //The table for keeping track of cards
	Player *player[4]; //4 players
	int startingPlayer;
	int currentPlayerNumber;
	int currentProgress;

	void invitePlayer(int number);
	bool doRound();
	void doTurn();
};

#endif
