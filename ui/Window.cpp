#include "Window.h"

Window::Window(Controller* c, Game* g)
	: controller(c), game(g),
	ui(false, 2), ui_controls(true, 2),
	ui_start("Start"), ui_quit("Quit"), 
	ui_seed_label("Seed:"), ui_table(true, 1),
	ui_hand(true, 1), ui_players(true, 2),
	ui_log_frame("Log")
{
	Logger.setConsole(&ui_log);
	Logger.log("Window: Loading...");

	//Table rows
	PixPtr empty = deck.empty();
	for(int i = 0; i < SUIT_COUNT; i++) {
		ui_table_rows[i] = Gtk::manage(new Gtk::HBox(true, 1));
	}
	//Table cells
	for(int i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
		ui_table_cells[i] = Gtk::manage(new Gtk::Image(empty));
		ui_table_cells[i]->set_padding(1, 1);
	}
	//Hand cells
	for(int i = 0; i < RANK_COUNT; i++) {
		ui_hand_cells[i] = Gtk::manage(new Gtk::EventBox());
		ui_hand_images[i] = Gtk::manage(new Gtk::Image(empty));
		ui_hand_images[i]->set_padding(1, 1);
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
	ui.pack_start(ui_controls, true, false, 2);
	ui.pack_start(ui_separator1, true, false);
	ui.pack_start(ui_progress, true, false);
	ui.pack_start(ui_table, true, false);
	ui.pack_start(ui_hand, true, false, 2);
	ui.pack_start(ui_players, true, false);
	ui.pack_start(ui_separator2, true, false);
	ui.pack_start(ui_log_frame, true, false, 2);

	//Controls
	ui_seed.set_text("0");
	ui_controls.pack_start(ui_seed_label, true, true);
	ui_controls.pack_start(ui_seed, true, true);
	ui_controls.pack_start(ui_start, true, true);
	ui_controls.pack_start(ui_quit, true, true);

	//Table
	for(int i = 0; i < SUIT_COUNT; i++) {
		ui_table.pack_start(*ui_table_rows[i], false, true);
	}
	//Table images
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			ui_table_rows[i]->pack_start(*ui_table_cells[i * RANK_COUNT + j], true, false);
		}
	}

	//Hand cells
	for(int i = 0; i < RANK_COUNT; i++) {
		ui_hand_cells[i]->add(*ui_hand_images[i]);
		ui_hand_cells[i]->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("green"));
		ui_hand.pack_start(*ui_hand_cells[i], true, true);
	}

	//Players
	for(int i = 0; i < 4; i++) {
		ui_players.pack_start(*ui_player_frame[i], true, true);
		ui_player_frame[i]->add(*ui_player_box[i]);
		ui_player_box[i]->pack_start(*ui_player_score[i], true, true);
		ui_player_box[i]->pack_start(*ui_player_discards[i], true, true);
	}

	//Log
	ui_log_frame.add(ui_log);

	show_all();

	game->subscribe(this);

	Logger.log("Window: Complete!");
}

Window::~Window()
{
	Logger.setConsole(NULL);
}

void Window::update()
{
	//Progress
	ui_progress.set_fraction(game->getProgress());

	//Table cards
	const Table *table = game->getTable();
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			if(table->played((Suit) i, (Rank) j)) {
				ui_table_cells[i * RANK_COUNT + j]->set(deck.image((Suit) i, (Rank) j));
			}
			else {
				ui_table_cells[i * RANK_COUNT + j]->set(deck.empty());
			}
		}
	}
}

void Window::handClicked()
{

}

void Window::buttonStartClicked()
{
	int seed = atoi(ui_seed.get_text().cstr());
}

void Window::buttonQuitClicked()
{

}
