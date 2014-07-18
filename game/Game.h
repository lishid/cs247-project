#ifndef _GAME_
#define _GAME_

#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Hand.h"
#include "Player.h"
#include "Command.h"
#include "../abstract/Subject.h"
#include "../ui/Log.h"
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

class Game : public Subject {
public:
	Game();
	virtual ~Game();
	void init(int seed);
	void newRound();
	void invitePlayer(int number, bool isHuman);
	void doTurn(Command&);
	void update();

	//Progress status
	double getProgress() const;

	//Table status
	bool getTableContainsCard(const Card &card) const;
	bool getTableCanPlay(const Card &card) const;
	bool getTableLastCard(const Card &card) const;

	//Hand status
	Card *getCurrentPlayerHand(int cardNumber) const;

	//Player status
	int getCurrentPlayerNumber() const;
	bool getPlayerExists(int playerNumber) const;
	bool getPlayerIsHuman(int playerNumber) const;
	int getPlayerScore(int playerNumber) const;
	int getPlayerDiscards(int playerNumber) const;
private:
	Deck deck; //The deck for shuffle and dealing
	Table table; //The table for keeping track of cards
	Hand *hands[4]; //4 hands
	Player *players[4]; //4 players
	int currentPlayerNumber;
	int currentTurnNumber;
	bool isPlaying;
};

#endif
