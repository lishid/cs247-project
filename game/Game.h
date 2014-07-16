#ifndef _GAME_
#define _GAME_

#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

class Game {
public:
	Game(int seed);
	virtual ~Game();
	void run();
private:
	Deck deck; //The deck for shuffle and dealing
	Table table; //The table for keeping track of cards
	Player *player[4]; //4 players
	int startingPlayer;
	int turnNumber;

	void invitePlayer(int number);
	bool doRound();
	void doTurn();
};

#endif
