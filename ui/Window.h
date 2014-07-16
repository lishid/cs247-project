#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm/window.h>

#include "DeckUI.h"

class Controller;
class Game;

class Window : public Gtk::Window, public Observer {
public:
	Window(Controller*, Game*);
	virtual ~Window();
	virtual void update();
private:
	Model *model;
	Controller *controller;
	DeckUI deck;

	//Overall frames in vertical space
	Gtk::VBox ui;

	//Game progress
	Gtk::ProgressBar ui_progress;

	//Table
	Gtk::VBox ui_table;
	
	//Hand
	Gtk::HBox ui_hand;

	//Controls
	Gtk::HBox ui_controls;
	Gtk::TextView ui_seed;
	Gtk::Button ui_start;
	Gtk::Button ui_quit;
	
	//Players
	Gtk::HBox ui_players;

	Gtk::Frame ui_player1;
	Gtk::Label ui_player1_score;
	Gtk::Label ui_player1_discards;

	Gtk::Frame ui_player2;
	Gtk::Label ui_player2_score;
	Gtk::Label ui_player2_discards;

	Gtk::Frame ui_player3;
	Gtk::Label ui_player3_score;
	Gtk::Label ui_player3_discards;

	Gtk::Frame ui_player4;
	Gtk::Label ui_player4_score;
	Gtk::Label ui_player4_discards;

	//Game log
	Gtk::TextView ui_log;

	void handClicked();
	void buttonStartClicked();
	void buttonQuitClicked();
};

#endif
