#ifndef PLAYERUI_H
#define PLAYERUI_H

#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>

#include "Log.h"
#include "../game/Player.h"

typedef Glib::RefPtr<Gdk::Pixbuf> PixPtr;

class PlayerUI {
public:
	PlayerUI();
	virtual ~PlayerUI();
	PixPtr image();
	PixPtr image(bool isHuman);
private:
	std::vector<PixPtr> images;
};

#endif
