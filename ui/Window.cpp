#include "Window.h"

namespace std
{
	inline string to_string(int val)
	{
		char buffer[64];
		snprintf(buffer, 64, "%d", val);
		return string(buffer);
	}
}

Window::Window(Controller* c, Game* g)
	: controller(c), game(g),
	ui(false, 2), ui_controls(false, 3),
	ui_start("  Start  "), ui_quit("  Quit  "), 
	ui_seed_label("  Seed: "), ui_announcer_label(" "),
	ui_table_frame("Cards on the table"), ui_table(true, 1),
	ui_hand(true, 1), ui_players(true, 3),
	ui_player_ragequit("   RAGEQUIT")
{
	ui_log_scrollable_container.add(ui_log);
	ui_log_frame.add(ui_log_scrollable_container);

	Logger.setConsole(&ui_log);
	Logger.setAnnounce(&ui_announcer_label);
	lout << "Straights is loading..." << lend;
	
	//Table rows
	PixPtr empty = deck.empty();
	for(int i = 0; i < SUIT_COUNT; i++) {
		ui_table_rows[i] = Gtk::manage(new Gtk::HBox(true, 0));
	}
	//Table cells
	for(int i = 0; i < SUIT_COUNT * RANK_COUNT; i++) {
		ui_table_cells[i] = Gtk::manage(new Gtk::Image(empty));
	}
	ui_table_frame.add(ui_table);
	
	//Hand cells
	for(int i = 0; i < RANK_COUNT; i++) {
		ui_hand_cells[i] = Gtk::manage(new Gtk::EventBox());
		ui_hand_align[i] = Gtk::manage(new Gtk::Alignment());
		ui_hand_buttons[i] = Gtk::manage(new Gtk::Button());
		ui_hand_images[i] = Gtk::manage(new Gtk::Image(empty));
	}
	//Players
	for(int i = 0; i < 4; i++) {
		char numstr[21];
		sprintf(numstr, "%d", i+1);
		ui_player_border[i] = Gtk::manage(new Gtk::EventBox());
		ui_player_frame[i] = Gtk::manage(new Gtk::Frame(string("Player ") + string(numstr)));
		ui_player_box[i] = Gtk::manage(new Gtk::HBox(false, 2));
		ui_player_vbox_right[i] = Gtk::manage(new Gtk::VBox(false, 2));
		ui_player_human[i] = Gtk::manage(new Gtk::Button("Human"));
		ui_player_computer[i] = Gtk::manage(new Gtk::Button("AI"));
		ui_player_score[i] = Gtk::manage(new Gtk::Label("Score: -"));
		ui_player_discards[i] = Gtk::manage(new Gtk::Label("Discards: -"));
		ui_player_type[i] = Gtk::manage(new Gtk::Image(empty));
	}

	//Window init
	set_title("Straights");
	set_border_width(5);
	add(ui);

	//Overall frames
	ui.pack_start(ui_controls, true, false, 2);
	ui.pack_start(ui_progress, true, false);
	ui.pack_start(ui_table_frame, true, false);
	ui.pack_start(ui_hand, true, false, 2);
	ui.pack_start(ui_players, true, false);
	ui.pack_start(ui_log_frame, true, false, 2);

	//Controls
	ui_seed.set_width_chars(10);
	ui_seed.set_text("0");
	ui_controls.pack_start(ui_start, false, false);
	ui_controls.pack_start(ui_seed_label, false, false);
	ui_controls.pack_start(ui_seed, false, false);
	ui_controls.pack_start(ui_announcer_label, true, true);
	ui_controls.pack_start(ui_quit, false, false);

	ui_start.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::buttonStartClicked));
	ui_quit.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::buttonQuitClicked));

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
		ui_hand.pack_start(*ui_hand_cells[i], true, true, 1);
		ui_hand_cells[i]->add(*ui_hand_align[i]);
		ui_hand_align[i]->add(*ui_hand_buttons[i]);
		ui_hand_buttons[i]->set_image(*ui_hand_images[i]);
		ui_hand_buttons[i]->signal_clicked().connect(
			sigc::mem_fun(*this, &Window::handClicked));
	}

	//Players
	ui_players.set_size_request(-1, 48);
	for(int i = 0; i < 4; i++) {
		ui_players.pack_start(*ui_player_frame[i], true, true);
		ui_player_frame[i]->add(*ui_player_border[i]);
		ui_player_border[i]->add(*ui_player_box[i]);
		ui_player_type[i]->set_size_request(0, -1);
		ui_player_vbox_right[i]->set_size_request(0, -1);
		ui_player_box[i]->pack_start(*ui_player_type[i], false, false, 3);
		ui_player_box[i]->pack_start(*ui_player_human[i], true, true, 3);
		ui_player_box[i]->pack_end(*ui_player_computer[i], true, true, 3);
		ui_player_box[i]->pack_start(*ui_player_vbox_right[i], true, true);
		ui_player_vbox_right[i]->pack_start(*ui_player_score[i], false, false);
		ui_player_vbox_right[i]->pack_start(*ui_player_discards[i], false, false);

		ui_player_human[i]->signal_clicked().connect(
			sigc::mem_fun(*this, &Window::buttonChooseClicked));
		ui_player_computer[i]->signal_clicked().connect(
			sigc::mem_fun(*this, &Window::buttonChooseClicked));
	}

	ui_player_ragequit_image.set(player.image());
	ui_player_ragequit.set_image(ui_player_ragequit_image);
	ui_player_ragequit.signal_clicked().connect(
		sigc::mem_fun(*this, &Window::buttonRageQuitClicked));
	ui_players.pack_start(ui_player_ragequit, true, true);

	//Log
	ui_log.set_size_request(-1, 100);
	ui_log.set_editable(false);
	ui_log.set_sensitive(false);
	ui_log.set_left_margin(3);
	show_all();

	game->subscribe(this);

	controller->newGame(0);
}

Window::~Window()
{
	Logger.setConsole(NULL);
}

void Window::update()
{
	int currentPlayer = game->getCurrentPlayerNumber();

	//Progress status
	ui_progress.set_fraction(game->getProgress());

	//Table status
	for(int i = 0; i < SUIT_COUNT; i++) {
		for(int j = 0; j < RANK_COUNT; j++) {
			Card card((Suit)i, (Rank)j);
			if(game->getTableContainsCard(card)) {
				ui_table_cells[i * RANK_COUNT + j]->set(deck.image(card, !game->getTableLastCard(card)));
			}
			else {
				ui_table_cells[i * RANK_COUNT + j]->set(deck.empty());
			}
		}
	}

	//Hand status
	for(int i = 0; i < RANK_COUNT; i++) {
		if(!game->getPlayerIsHuman(currentPlayer)) {
			ui_hand_images[i]->set(deck.back());
			ui_hand_buttons[i]->set_sensitive(false);
		}
		else {
			Card *card = game->getCurrentPlayerHand(i);
			if(card != NULL) {
				ui_hand_images[i]->set(deck.image(*card, !game->getTableCanPlay(*card)));
				ui_hand_buttons[i]->set_sensitive(true);
			}
			else {
				ui_hand_images[i]->set(deck.empty());
				ui_hand_buttons[i]->set_sensitive(false);
			}
		}
	}

	//Player status
	for(int i = 0; i < 4; i++) {
		bool isCurrentPlayer = i == currentPlayer;
		int score = game->getPlayerScore(i);
		int discards = game->getPlayerDiscards(i);

		if(!game->getPlayerExists(i))
		{
			isCurrentPlayer = false;
			ui_player_human[i]->show();
			ui_player_computer[i]->show();
			ui_player_type[i]->hide();
			ui_player_vbox_right[i]->hide();
		}
		else {
			ui_player_type[i]->set(player.image(game->getPlayerIsHuman(i), isCurrentPlayer));
			ui_player_human[i]->hide();
			ui_player_computer[i]->hide();
			ui_player_type[i]->set_size_request(-1, -1);
			ui_player_vbox_right[i]->set_size_request(-1, -1);
			ui_player_type[i]->show();
			ui_player_vbox_right[i]->show();
		}
		
		ui_player_score[i]->set_text(std::string("Score: ") + std::to_string(score));
		ui_player_discards[i]->set_text(std::string("Discards: ") + std::to_string(discards));
	}

	if(game->isInProgress() && !game->getPlayerIsHuman(currentPlayer)) {
		timeout.disconnect();
		sigc::slot<bool> slot = sigc::bind(sigc::mem_fun(*this, &Window::aiTimeout), 0);
		timeout = Glib::signal_timeout().connect(slot, 500);
	}
}


void Window::buttonChooseClicked()
{
	for(int i = 0; i < 4; i++) {
		if(ui_player_human[i]->has_focus()) {
			controller->invitePlayer(i, true);
			break;
		}
		else if(ui_player_computer[i]->has_focus()) {
			controller->invitePlayer(i, false);
			break;
		}
	}
}

void Window::handClicked()
{
	for(int i = 0; i < RANK_COUNT; i++) {
		if(ui_hand_buttons[i]->has_focus()) {
			controller->clickCard(i);
			break;
		}
	}
}

void Window::buttonStartClicked()
{
	int seed = atoi(ui_seed.get_text().c_str());
	controller->newGame(seed);
}

void Window::buttonQuitClicked()
{
	exit(0);
}

void Window::buttonRageQuitClicked()
{
	controller->ragequit();
}

bool Window::aiTimeout(int timer)
{
	timeout.disconnect();
	controller->aiTimeout();
	return true;
}
