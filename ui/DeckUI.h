#ifndef DECKUI_H
#define DECKUI_H

#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

#include "Log.h"
#include "../game/Card.h"

typedef Glib::RefPtr<Gdk::Pixbuf> PixPtr;

class DeckUI {
public:
	DeckUI();
	virtual ~DeckUI();
	PixPtr image(Suit suit, Rank rank, bool isDisabled);
	PixPtr image(const Card &card, bool isDisabled);
	PixPtr empty();
private:
	std::vector<PixPtr> deck;
	std::vector<PixPtr> deck_disabled;
};

#endif
