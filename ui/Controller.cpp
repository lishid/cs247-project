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
			game->doTurn(Command(PLAY, *card));
		}
		else {
			game->doTurn(Command(DISCARD, *card));
		}
	}
}

void Controller::ragequit()
{
	game->doTurn(Command(RAGEQUIT));
}

void Controller::aiTimeout()
{
	game->doTurn(Command(AI));
}
