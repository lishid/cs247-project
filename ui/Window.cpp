#include "Window.h"

Window::Window(Controller* c, Game* g)
	: controller(c), game(g),
	ui(true, 10), ui_table(true, 10),
	ui_hand(true, 10), ui_controls(true, 10),
	ui_start("Start"), ui_quit("Quit"), 
	ui_players(true, 10)
{
	set_title( "Straights" );
	set_border_width( 10 );
	add(ui);

	ui_seed.set_text("0");

	//Overall frames
	ui.pack_start(ui_progress, true, false);
	ui.pack_start(ui_table, true, false);
	ui.pack_start(ui_hand, true, false);
	ui.pack_start(ui_controls, true, false);
	ui.pack_start(ui_players, true, false);
	ui.pack_start(ui_log, true, false);


	show_all();

	//game->subscribe(this);
}

Window::~Window()
{

}

void Window::update()
{

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
