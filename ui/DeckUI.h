#ifndef DECKUI_H
#define DECKUI_H

#include <gdkmm/pixbuf.h>
#include <vector>

#include "../game/card.h"

typedef Glib::RefPtr<Gdk::Pixbuf> PixPtr;

class DeckUI {
public:
	DeckUI();
	virtual ~DeckUI();
	PixPtr image(Suit suit, Rank rank);
	PixPtr empty();
private:
	std::vector<PixPtr> deck;
};

#endif