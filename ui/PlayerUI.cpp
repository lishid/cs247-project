#include "PlayerUI.h"

using namespace std;

const char * other_names[] = {
	"img/AI.png",
	"img/Human.png",
	"img/EndOfHuman.png"
}; 

PlayerUI::PlayerUI()  {
	// lout << "Loading player images..." << lend;
	int size = G_N_ELEMENTS(other_names);
	for(int i = 0; i < size; i++) {
		images.push_back(Gdk::Pixbuf::create_from_file(string(other_names[i])));
	}
	// lout << "Loaded player images." << lend;
}

PlayerUI::~PlayerUI() {
}

PixPtr PlayerUI::image() {
	return images[2];
}

PixPtr PlayerUI::image(bool isHuman) {
	return isHuman ? images[1] : images[0];
}
