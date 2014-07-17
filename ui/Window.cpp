#include "Window.h"

Window::Window(Controller* c, Game* g)
	: controller(c), game(g),
	ui(true, 0), ui_table(true, 1),
	ui_hand(true, 1), ui_controls(true, 2),
	ui_start("Start"), ui_quit("Quit"), 
	ui_players(true, 2)
{
	Logger.setConsole(&ui_log);
	Logger.log("Loading...");

	//Table rows
	PixPtr empty = deck.empty();
	for(int i = 0; i < SUIT_COUNT; i++) {
		ui_table_rows[i] = Gtk::manage(new Gtk::HBox(true, 1));
	}
	//Table cells
	for(int i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
		ui_table_cells[i] = Gtk::manage(new Gtk::Image(empty));
	}
	//Hand cells
	for(int i = 0; i < RANK_COUNT; i++) {
		ui_hand_cells[i] = Gtk::manage(new Gtk::Image(empty));
	}
	//Players
	for(int i = 0; i < 4; i++) {
		char numstr[21];
		sprintf(numstr, "%d", i);
		ui_player_frame[i] = Gtk::manage(new Gtk::Frame(string("Player ") + string(numstr)));
		ui_player_box[i] = Gtk::manage(new Gtk::VBox(true, 2));
		ui_player_score[i] = Gtk::manage(new Gtk::Label("test"));
		ui_player_discards[i] = Gtk::manage(new Gtk::Label("test"));
	}

	//Window init
	set_title("Straights");
	set_border_width(5);
	add(ui);

	//Overall frames
	ui.pack_start(ui_progress, true, false);
	for(int i = 0; i < SUIT_COUNT; i++) {
		ui.pack_start(*ui_table_rows[i], true, false);
	}
	ui.pack_start(ui_hand, true, false);
	ui.pack_start(ui_controls, true, false);
	ui.pack_start(ui_players, true, false);
	ui.pack_start(ui_log, true, false);

	//Table images
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			ui_table_rows[i]->pack_start(*ui_table_cells[i * RANK_COUNT + j], true, false);
		}
	}

	//Hand cells
	for(int i = 0; i < RANK_COUNT; i++) {
		ui_hand.pack_start(*ui_hand_cells[i], true, false);
	}

	//Controls
	ui_seed.set_text("0");
	ui_controls.pack_start(ui_seed, true, false);
	ui_controls.pack_start(ui_start, true, false);
	ui_controls.pack_start(ui_quit, true, false);

	//Players
	for(int i = 0; i < 4; i++) {
		ui_players.pack_start(*ui_player_frame[i], true, false);
		ui_player_frame[i]->add(*ui_player_box[i]);
		ui_player_box[i]->pack_start(*ui_player_score[i], true, false);
		ui_player_box[i]->pack_start(*ui_player_discards[i], true, false);
	}

	show_all();

	//game->subscribe(this);
	Logger.log("Complete!");
}

Window::~Window()
{
	Logger.setConsole(NULL);
}

void Window::update()
{
	//Progress
	double progress = 1;
	ui_progress.set_fraction(progress);


}

void Window::handClicked()
{

}

void Window::buttonStartClicked()
{

}

void Window::buttonQuitClicked()
{

}
