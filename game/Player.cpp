#include "Player.h"

using namespace std;

Player::Player(int playerNumber) : playerNumber(playerNumber), score(0)
{
	clear();
}

Player::Player(Player *player)
	 : playerNumber(player->playerNumber), score(player->score)
{
	for(int i = 0; i < RANK_COUNT; i++) {
		cards[i] = player->cards[i];
		discards[i] = player->discards[i];
	}
}

Player::~Player()
{

}

int Player::endRound()
{
	int additionalScore = 0;

	cout << "Player " << playerNumber << "'s discards: ";
	for(int i = 0; i < RANK_COUNT; i++) {
		if(discards[i] != NULL) {
			cout << *discards[i];
			additionalScore += discards[i]->getScore();
			if(i != RANK_COUNT - 1) {
				cout << " ";
			}
		}
	}
	cout << endl;
	
	int newScore = score + additionalScore;
	cout << "Player " << playerNumber << "'s score: " << score << " + " << additionalScore << " = " << newScore << endl;
	score = newScore;

	//Cleanup
	clear();
	return score;
}

int Player::getScore() const
{
	return score;
}

int Player::getPlayerNumber() const
{
	return playerNumber;
}

Card **Player::getCards()
{
	return cards;
}

void Player::printHand() const
{
	cout << "Your hand:";
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			cout << " " << *cards[i];
		}
	}
	cout << endl;
}

void Player::printLegalPlays(const Table &table) const
{
	cout << "Legal Plays:";
	for(int i = 0; i < RANK_COUNT; i++) {
		if(table.canPlay(*cards[i])) {
			cout << " " << *cards[i];
		}
	}
	cout << endl;
}

bool Player::canPlay(const Table &table, const Card *card) const
{
	//Ensure card can be played
	if(!table.canPlay(*card)) {
		return false;
	}

	//Ensure player has card
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			if(table.canPlay(*cards[i])) {
				cout << " " << *cards[i];
			}
		}
	}

	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			if(*cards[i] == *card) {
				return true;
			}
		}
	}

	return false;
}

bool Player::canDiscard(const Table &table, const Card *card) const
{
	bool hasCard = false;
	//Ensure player has card and can't play other cards
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			//Ensure no cards can be played
			if(table.canPlay(*cards[i])) {
				return false;
			}

			if(*cards[i] == *card) {
				hasCard = true;
			}
		}
	}
	return hasCard;
}

Card *Player::remove(Card *card)
{
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			if(*cards[i] == *card) {
				card = cards[i];
				cards[i] = NULL;
				return card;
			}
		}
	}
	return NULL;
}

void Player::clear()
{
	for(int i = 0; i < RANK_COUNT; i++) {
		cards[i] = NULL;
		discards[i] = NULL;
	}
}

void Player::play(Table &table, Card *card)
{
	Card *c = remove(card);
	table.play(*c);
	cout << "Player " << playerNumber << " plays " << *card << "." << endl;
}

void Player::discard(Card *card)
{
	Card *c = remove(card);
	for(int i = 0; i < RANK_COUNT; i++) {
		if(discards[i] == NULL) {
			discards[i] = c;
		}
	}
	cout << "Player " << playerNumber << " discards " << *card << "." << endl;
}

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber)
{

}

ComputerPlayer::ComputerPlayer(Player *player) : Player(player)
{
	delete player;
}

Type ComputerPlayer::turn(Table &table, bool print)
{
	Card** cards = getCards();
	for(int i = 0; i < RANK_COUNT; i++) {
		if(cards[i] != NULL) {
			if(table.canPlay(*cards[i])) {
				play(table, cards[i]);
				return PLAY;
			}
		}
	}
	
	discard(cards[0]);
	return DISCARD;
}


HumanPlayer::HumanPlayer(int playerNumber) : Player(playerNumber)
{

}

Type HumanPlayer::turn(Table &table, bool print)
{
	if(print) {
		//Print table
		table.print();
		//Print your hand
		printHand();
		//Print legal plays
		printLegalPlays(table);
	}
	//Take command
	Command c;
	while(true) {
		cout << ">";
		cin >> c;

		switch(c.type) {
		case PLAY:
			if(canPlay(table, &c.card)) {
				play(table, &c.card);
				return c.type;
			}
			else {
				cout << "This is not a legal play." << endl;
			}
			break;
		case DISCARD:
			if(canDiscard(table, &c.card)) {
				discard(&c.card);
				return c.type;
			}
			else {
				cout << "You have a legal play. You may not discard." << endl;
			}
			break;
		case RAGEQUIT:
			cout << "Player " << getPlayerNumber() << " ragequits. A computer will now take over." << endl;
			return c.type;
			break;
		case DECK:
		case QUIT:
		case BAD_COMMAND:
			return c.type;
			break;
		}
	}
}
