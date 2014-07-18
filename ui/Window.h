#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>
#include <stdio.h>

#include "../abstract/Observer.h"
#include "../game/Game.h"
#include "../game/Card.h"
#include "../ui/Controller.h"
#include "DeckUI.h"
#include "PlayerUI.h"

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
	PlayerUI player;

	//Overall frames in vertical space
	Gtk::VBox ui;
	
	//Controls
	Gtk::HBox ui_controls;
	Gtk::Button ui_start;
	Gtk::Button ui_quit;
	Gtk::Label ui_seed_label;
	Gtk::Entry ui_seed;

	//Game progress
	Gtk::ProgressBar ui_progress;

	//Table
	Gtk::Frame ui_table_frame;
	Gtk::VBox ui_table;
	Gtk::HBox *ui_table_rows[SUIT_COUNT];
	Gtk::Image *ui_table_cells[SUIT_COUNT * RANK_COUNT];
	
	//Hand
	Gtk::HBox ui_hand;
	Gtk::EventBox *ui_hand_cells[RANK_COUNT];
	Gtk::Alignment *ui_hand_align[RANK_COUNT];
	Gtk::Button *ui_hand_buttons[RANK_COUNT];
	Gtk::Image *ui_hand_images[RANK_COUNT];
	
	//Players
	Gtk::HBox ui_players;

	Gtk::EventBox *ui_player_border[4];
	Gtk::Frame *ui_player_frame[4];
	Gtk::HBox *ui_player_box[4];
	Gtk::VBox *ui_player_vbox_right[4];
	Gtk::Button *ui_player_human[4];
	Gtk::Button *ui_player_computer[4];
	Gtk::Image *ui_player_type[4];
	Gtk::Label *ui_player_score[4];
	Gtk::Label *ui_player_discards[4];
	Gtk::Button ui_player_ragequit;
	Gtk::Image ui_player_ragequit_image;

	//Game log
	Gtk::Frame ui_log_frame;
	Gtk::ScrolledWindow ui_log_scrollable_container;
	Gtk::TextView ui_log;

	sigc::connection timeout;

	void handClicked();
	void buttonChooseClicked();
	void buttonStartClicked();
	void buttonQuitClicked();
	bool aiTimeout(int timer);
};

#endif
