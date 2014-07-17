#include "Game.h"

using namespace std;

Game::Game()
{
	srand48(0);
}

Game::~Game()
{

}

const Table *Game::getTable() const
{
	return &table;
}

const Player *Game::getPlayer(int number) const
{
	return player[number];
}

int Game::getCurrentPlayer() const
{
	return currentPlayerNumber;
}

double Game::getProgress() const
{
	double result = currentProgress;
	result /= SUIT_COUNT * RANK_COUNT;
	return result;
}

void Game::run()
{
	//Invite players
	for(int i = 0; i < 4; i++) {
		invitePlayer(i);
	}
	

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
	}
}

void Game::invitePlayer(int index)
{
	cout << "Is player " << (index + 1) << " a human(h) or a computer(c)?" << endl << ">";
	char c;
	cin >> c;
	
	assert(c == 'c' || c == 'C' || c == 'h' || c == 'H');
	if(c == 'c' || c == 'C') {
		player[index] = new ComputerPlayer(index + 1);
	}
	else if(c == 'h' || c == 'H') {
		player[index] = new HumanPlayer(index + 1);
	}
}

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

void Game::doTurn()
{
	//Iterate 4 players
	for(int i = 0; i < 4; i++) {
		int p = (i + startingPlayer) % 4;
		bool first = true;
		while(true) {
			Type command = player[p]->turn(table, first);
			first = false;
			if(command == PLAY || command == DISCARD) {
				break;
			}

			switch(command) {
			case PLAY:
			case DISCARD:
				break;

			case DECK:
				//deck.print();
				break;

			case QUIT:
			case BAD_COMMAND:
				exit(0);
				break;

			case RAGEQUIT:
				player[p] = new ComputerPlayer(player[p]);
				break;
			}
		}
	}
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
