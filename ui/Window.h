#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>

#include "../abstract/Observer.h"
#include "../game/Game.h"
#include "../game/Card.h"
#include "../ui/Controller.h"
#include "DeckUI.h"

class Controller;
class Game;

class Window : public Gtk::Window, public Observer {
public:
	Window(Controller*, Game*);
	virtual ~Window();
	virtual void update();
private:
	Controller *controller;
	Game *game;
	DeckUI deck;

	//Overall frames in vertical space
	Gtk::VBox ui;

	//Game progress
	Gtk::ProgressBar ui_progress;

	//Table
	Gtk::VBox ui_table;
	Gtk::HBox *ui_table_rows[SUIT_COUNT];
	Gtk::Image *ui_table_cells[SUIT_COUNT * RANK_COUNT];
	
	//Hand
	Gtk::HBox ui_hand;
	Gtk::Image *ui_hand_cells[RANK_COUNT];
	
	//Controls
	Gtk::HBox ui_controls;
	Gtk::Entry ui_seed;
	Gtk::Button ui_start;
	Gtk::Button ui_quit;
	
	//Players
	Gtk::HBox ui_players;

	Gtk::Frame *ui_player_frame[4];
	Gtk::VBox *ui_player_box[4];
	Gtk::Label *ui_player_score[4];
	Gtk::Label *ui_player_discards[4];

	//Game log
	Gtk::TextView ui_log;

	void handClicked();
	void buttonStartClicked();
	void buttonQuitClicked();
};

#endif
