#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../game/Game.h"

class Controller {
public:
	Controller(Game*);
	void newGame(int seed);
	void invitePlayer(int number, bool isHuman);
	void clickCard(int cardNumber);
	void aiTimeout();
	void ragequit();
private:
	Game *game;
};

#endif
