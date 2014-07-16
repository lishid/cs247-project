#include "Player.h"

using namespace std;

Player::Player(int playerNumber) : playerNumber(playerNumber), score(0)
{

}

Player::Player(int playerNumber, int score, std::vector<Card*> cards, std::vector<Card*> discards)
	 : playerNumber(playerNumber), score(score), cards(cards), discards(discards)
{

}

Player::~Player()
{

}

void Player::giveCards(std::vector<Card*> newCards)
{
	cards = newCards;
}

int Player::endRound()
{
	int additionalScore = 0;

	cout << "Player " << playerNumber << "'s discards: ";
	for(vector<Card*>::iterator it = discards.begin() ; it != discards.end(); ) {
		cout << **it;
		additionalScore += (*it)->getScore();
		++it;
		if(it != discards.end()) {
			cout << " ";
		}
	}
	cout << endl;
	
	int newScore = score + additionalScore;
	cout << "Player " << playerNumber << "'s score: " << score << " + " << additionalScore << " = " << newScore << endl;
	score = newScore;

	//Cleanup
	cards.clear();
	discards.clear();
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

vector<Card*> Player::getDiscards() const
{
	return discards;
}

vector<Card*> Player::getCards() const
{
	return cards;
}

void Player::printHand() const
{
	cout << "Your hand:";
	for(vector<Card*>::const_iterator it = cards.begin() ; it != cards.end(); ) {
		cout << " " << **it;
		++it;
	}
	cout << endl;
}

void Player::printLegalPlays(const Table &table) const
{
	cout << "Legal Plays:";
	for(vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		if(table.canPlay(**it)) {
			cout << " " << **it;
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
	for(vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		if((**it) == *card) {
			return true;
		}
	}

	return false;
}

bool Player::canDiscard(const Table &table, const Card *card) const
{
	bool hasCard = false;
	//Ensure player has card and can't play other cards
	for(vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		//Ensure no cards can be played
		if(table.canPlay(**it)) {
			return false;
		}

		if((**it) == *card) {
			hasCard = true;
		}
	}
	return hasCard;
}

Card *Player::remove(Card *card)
{
	for(vector<Card*>::iterator it = cards.begin(); it != cards.end(); ++it) {
		if(**it == *card) {
			card = *it;
			cards.erase(it);
			return card;
		}
	}
	return NULL;
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
	discards.push_back(c);
	cout << "Player " << playerNumber << " discards " << *card << "." << endl;
}

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber)
{

}

ComputerPlayer::ComputerPlayer(Player *player) : Player(player->getPlayerNumber(), player->getScore(), player->getCards(), player->getDiscards())
{
	delete player;
}

Type ComputerPlayer::turn(Table &table, bool print)
{
	vector<Card*> cards = getCards();
	for(vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		if(table.canPlay(**it)) {
			play(table, *it);
			return PLAY;
		}
	}
	
	discard(*cards.begin());
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



