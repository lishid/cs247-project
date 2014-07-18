#include "Controller.h"

Controller::Controller(Game* g) : game(g)
{
	
}

void Controller::newGame(int seed)
{
	game->init(seed);
}

void Controller::invitePlayer(int number, bool isHuman)
{
	game->invitePlayer(number, isHuman);
}

void Controller::clickCard(int cardNumber)
{
	int currentPlayer = game->getCurrentPlayerNumber();
	if(game->getPlayerIsHuman(currentPlayer)) {
		Card *card = game->getCurrentPlayerHand(cardNumber);
		if(card == NULL) {
			return;
		}
		if(game->getTableCanPlay(*card)) {
			Command c(PLAY, *card);
			game->doTurn(c);
		}
		else {
			Command c(DISCARD, *card);
			game->doTurn(c);
		}
	}
}