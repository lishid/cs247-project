#include "DeckUI.h"

using namespace std;

const char * image_names[] = {
	"img/0_0.png", "img/0_1.png", "img/0_2.png",
	"img/0_3.png", "img/0_4.png", "img/0_5.png",
	"img/0_6.png", "img/0_7.png", "img/0_8.png",
	"img/0_9.png", "img/0_j.png", "img/0_q.png", "img/0_k.png",

	"img/1_0.png", "img/1_1.png", "img/1_2.png",
	"img/1_3.png", "img/1_4.png", "img/1_5.png",
	"img/1_6.png", "img/1_7.png", "img/1_8.png",
	"img/1_9.png", "img/1_j.png", "img/1_q.png", "img/1_k.png",

	"img/2_0.png", "img/2_1.png", "img/2_2.png",
	"img/2_3.png", "img/2_4.png", "img/2_5.png",
	"img/2_6.png", "img/2_7.png", "img/2_8.png",
	"img/2_9.png", "img/2_j.png", "img/2_q.png", "img/2_k.png",

	"img/3_0.png", "img/3_1.png", "img/3_2.png",
	"img/3_3.png", "img/3_4.png", "img/3_5.png",
	"img/3_6.png", "img/3_7.png", "img/3_8.png",
	"img/3_9.png", "img/3_j.png", "img/3_q.png", "img/3_k.png",

	"img/nothing.png", "img/back.png"
}; 

const char * image_disabled_names[] = {
	"img/0_0_a.png", "img/0_1_a.png", "img/0_2_a.png",
	"img/0_3_a.png", "img/0_4_a.png", "img/0_5_a.png",
	"img/0_6_a.png", "img/0_7_a.png", "img/0_8_a.png",
	"img/0_9_a.png", "img/0_j_a.png", "img/0_q_a.png", "img/0_k_a.png",

	"img/1_0_a.png", "img/1_1_a.png", "img/1_2_a.png",
	"img/1_3_a.png", "img/1_4_a.png", "img/1_5_a.png",
	"img/1_6_a.png", "img/1_7_a.png", "img/1_8_a.png",
	"img/1_9_a.png", "img/1_j_a.png", "img/1_q_a.png", "img/1_k_a.png",

	"img/2_0_a.png", "img/2_1_a.png", "img/2_2_a.png",
	"img/2_3_a.png", "img/2_4_a.png", "img/2_5_a.png",
	"img/2_6_a.png", "img/2_7_a.png", "img/2_8_a.png",
	"img/2_9_a.png", "img/2_j_a.png", "img/2_q_a.png", "img/2_k_a.png",

	"img/3_0_a.png", "img/3_1_a.png", "img/3_2_a.png",
	"img/3_3_a.png", "img/3_4_a.png", "img/3_5_a.png",
	"img/3_6_a.png", "img/3_7_a.png", "img/3_8_a.png",
	"img/3_9_a.png", "img/3_j_a.png", "img/3_q_a.png", "img/3_k_a.png"
}; 

DeckUI::DeckUI()  {
	// lout << "Loading deck images..." << lend;
	int size = G_N_ELEMENTS(image_names);
	for(int i = 0; i < size; i++) {
		deck.push_back(Gdk::Pixbuf::create_from_file(string(image_names[i])));
		deck_disabled.push_back(Gdk::Pixbuf::create_from_file(string(image_disabled_names[i])));
	}
	// lout << "Loaded deck images." << lend;
}

DeckUI::~DeckUI() {
}

PixPtr DeckUI::image(const Card &card, bool isDisabled) {
	return image(card.getSuit(), card.getRank(), isDisabled);
}

PixPtr DeckUI::image(Suit suit, Rank rank, bool isDisabled) {
	int index = ((int) suit) * RANK_COUNT + ((int) rank);
	return isDisabled ? deck_disabled[index] : deck[index];
}

PixPtr DeckUI::empty() {
	return deck[deck.size() - 2];
}

PixPtr DeckUI::back() {
	return deck[deck.size() - 1];
}
