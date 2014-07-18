#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"

enum CommandType { PLAY, DISCARD, RAGEQUIT, AI, BAD };

struct Command {
	CommandType type;
	Card card;
	Command(CommandType t, Card c) : type(t), card(c) {}
	Command(CommandType t) : type(t), card(Card(CLUB, ACE)) {}
};

#endif