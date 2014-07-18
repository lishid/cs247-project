#include "Game.h"

using namespace std;

Game::Game() : currentPlayerNumber(0), currentTurnNumber(0), isPlaying(false)
{
	for(int i = 0; i < 4; i++) {
		hands[i] = new Hand();
		players[i] = NULL;
	}
}

Game::~Game()
{
	for(int i = 0; i < 4; i++) {
		delete hands[i];
		delete players[i];
	}
}

//Progress status
double Game::getProgress() const
{
	if(currentTurnNumber > SUIT_COUNT * RANK_COUNT) {
		return 1;
	}
	return (double)currentTurnNumber / (double) SUIT_COUNT / (double) RANK_COUNT;
}

//Table status
bool Game::getTableContainsCard(const Card &card) const
{
	return table.played(card);
}

bool Game::getTableCanPlay(const Card &card) const
{
	return table.canPlay(card);
}

bool Game::getTableLastCard(const Card &card) const
{
	return table.isLastCard(card);
}

//Hand status
Card *Game::getCurrentPlayerHand(int cardNumber) const
{
	return hands[currentPlayerNumber]->getCard(cardNumber);
}

//Player status
int Game::getCurrentPlayerNumber() const
{
	return currentPlayerNumber;
}

bool Game::getPlayerExists(int playerNumber) const
{
	return players[playerNumber] != NULL;
}

bool Game::getPlayerIsHuman(int playerNumber) const
{
	if(!players[playerNumber]) {
		return false;
	}
	return players[playerNumber]->isHuman();
}

int Game::getPlayerScore(int playerNumber) const
{
	return hands[playerNumber]->getScore();
}

int Game::getPlayerDiscards(int playerNumber) const
{
	return hands[playerNumber]->getDiscards();
}

void Game::init(int seed)
{
	srand48(seed);

	//Clear players
	for(int i = 0; i < 4; i++) {
		if(players[i]) {
			delete players[i];
		}
		players[i] = NULL;
		hands[i]->reset();
	}

	isPlaying = false;
	currentTurnNumber = 0;
	currentPlayerNumber = 0;

	lout << "A new game has started." << lend;

	lout << "Please select a type for each player." << lend;

	update();
}

void Game::newRound()
{
	//Shuffle first
	deck.shuffle();

	//Clear table
	table.reset();

	//Pass cards to players
	for(int i = 0; i < 4; i++) {
		hands[i]->deal(deck.deal(i));
	}

	//Find starting player
	currentPlayerNumber = deck.findStartingPlayer();
	currentTurnNumber = 0;
	
	lout << "A new round begins. It's player " << (currentPlayerNumber + 1) << "'s turn to play." << lend;

	isPlaying = true;

	update();
}

void Game::invitePlayer(int index, bool isHuman)
{
	if(getPlayerExists(index)) {
		return;
	}
	lout << "Player " << (index + 1) << " is a ";
	if(isHuman) {
		lout << "human." << lend;
		players[index] = new HumanPlayer(index + 1, hands[index]);
	}
	else {
		players[index] = new ComputerPlayer(index + 1, hands[index]);
		lout << "computer." << lend;
	}
	update();
}

void Game::doTurn(Command &command)
{
	CommandType type = players[currentPlayerNumber]->act(table, command);

	switch(type) {
	case PLAY:
	case DISCARD:
		break;
	case RAGEQUIT:
		players[currentPlayerNumber] = new ComputerPlayer(players[currentPlayerNumber]);
	case BAD:
		return;
	}
	currentPlayerNumber = (currentPlayerNumber + 1) % 4;
	currentTurnNumber++;
	update();
}

void Game::update()
{
	//Check if end of game
	if(currentTurnNumber >= SUIT_COUNT * RANK_COUNT) {
		//End of game: stop game
		isPlaying = false;
		//Check scores
		int maxScore = 0;
		for(int i = 0; i < 4; i++) {
			hands[i]->endRound();
			int score = hands[i]->getScore();
			if(score > maxScore) {
				maxScore = score;
			}
		}

		if(maxScore >= 80) {
			//Game is finished.
			//Print Winners
			int minScore = 81;
			for(int i = 0; i < 4; i++) {
				int score = hands[i]->getScore();
				if(score < minScore) {
					minScore = score;
				}
			}
			
			for(int i = 0; i < 4; i++) {
				int score = hands[i]->getScore();
				if(score == minScore) {
					lout << "Player " << (i+1) << " wins!" << lend;
					currentPlayerNumber = i;
				}
			}
		}
		else {
			//Re-start a new round
			newRound();
		}
	}
	//Pre-game, check if we're ready to start
	else if(!isPlaying) {
		int numPlayers = 0;
		for(int i = 0; i < 4; i++) {
			if(getPlayerExists(i)) {
				numPlayers++;
			}
		}
		if(numPlayers == 4) {
			//Start game!
			newRound();
		}
	}
	else {
		//Let computers play
		if(isPlaying && !getPlayerIsHuman(currentPlayerNumber)) {
			Command c(PLAY, Card(CLUB, ACE));
			doTurn(c);
		}
	}

	notify();
}
