#include "Game.h"

using namespace std;

Game::Game()
{
	for(int i = 0; i < 4; i++) {
		hands[i] = new Hand();
	}
}

Game::~Game()
{
	for(int i = 0; i < 4; i++) {
		delete hands[i];
		delete player[i];
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

bool Game::getPlayerIsHuman(int playerNumber) const
{
	return player[playerNumber]->isHuman();
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

	//Invite players
	for(int i = 0; i < 4; i++) {
		invitePlayer(i);
	}

/*
	bool highscore = false;
	while(!highscore) {
		highscore = doRound();
		//Restart if score is not high enough
	}

	//Print Winners
	int minScore = 81;
	for(int i = 0; i < 4; i++) {
		int score = player[i]->getScore();
		if(score < minScore) {
			minScore = score;
		}
	}
	
	for(int i = 0; i < 4; i++) {
		int score = player[i]->getScore();
		if(score == minScore) {
			cout << "Player " << (i+1) << " wins!" << endl;
		}
	}*/
}

void Game::invitePlayer(int index)
{/*
	cout << "Is player " << (index + 1) << " a human(h) or a computer(c)?" << endl << ">";
	char c;
	cin >> c;
	
	assert(c == 'c' || c == 'C' || c == 'h' || c == 'H');
	if(c == 'c' || c == 'C') {
		player[index] = new ComputerPlayer(index + 1);
	}
	else if(c == 'h' || c == 'H') {
		player[index] = new HumanPlayer(index + 1);
	}*/
}
/*
bool Game::doRound()
{
	//Shuffle first
	deck.shuffle();

	//Clear table
	table.reset();

	//Pass cards to players
	for(int i = 0; i < 4; i++) {
		deck.deal(i, player[i]->getCards());
	}

	//Find starting player
	startingPlayer = deck.findStartingPlayer();
	
	cout << "A new round begins. It's player " << (startingPlayer + 1) << "'s turn to play." << endl;

	//Play 13 turns
	for(int t = 0; t < 13; t++) {
		doTurn();
	}

	//Check scores
	int maxScore = 0;
	for(int i = 0; i < 4; i++) {
		int score = player[i]->endRound();
		if(score > maxScore) {
			maxScore = score;
		}
	}

	return maxScore >= 80;
}
*/
void Game::doTurn(Command &command)
{
	CommandType type = player[currentPlayerNumber]->act(table, command);

	switch(type) {
	case PLAY:
	case DISCARD:
		break;
	case RAGEQUIT:
		player[currentPlayerNumber] = new ComputerPlayer(player[currentPlayerNumber]);
	case BAD:
		return;
	}
	currentPlayerNumber = (currentPlayerNumber + 1) % 4;
	currentTurnNumber++;
}

//int main(int argc, char* argv[])
//{
//	int seed = 0;
//	if(argc > 1) {
//		seed = atoi(argv[1]);
//	}
///	Game g =  Game(seed);
//	g.run();
//	return 0;
//}
